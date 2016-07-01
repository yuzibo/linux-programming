Files in the standard library are described by file pointers rather than file descriptors. A file pointer is a pointer to a structure that contains several pieces of information about the file: a pointer to a buffer, so the file can be read in large chunks; a count of the number of characters left in the buffer; a pointer to the next character position in the buffer; the file descriptor; and flags describing read/write mode, error status, etc.

The data structure that describes a file is contained in <stdio.h>, which must be included (by #include) in any source file that uses routines from the standard input/output library. It is also included by functions in that library. In the following excerpt from a typical <stdio.h>, names that are intended for use only by functions of the library begin with an underscore so they are less likely to collide with names in a user's program. This convention is used by all standard library routines.

   #define NULL      0
   #define EOF       (-1)
   #define BUFSIZ    1024
   #define OPEN_MAX  20    /* max #files open at once */

   typedef struct _iobuf {
       int  cnt;       /* characters left */
       char *ptr;      /* next character position */
       char *base;     /* location of buffer */
       int  flag;      /* mode of file access */
       int  fd;        /* file descriptor */
   } FILE;
   extern FILE _iob[OPEN_MAX];

   #define stdin   (&_iob[0])
   #define stdout  (&_iob[1])
   #define stderr  (&_iob[2])

   enum _flags {
       _READ   = 01,   /* file open for reading */
       _WRITE  = 02,   /* file open for writing */
       _UNBUF  = 04,   /* file is unbuffered */
       _EOF    = 010,  /* EOF has occurred on this file */
       _ERR    = 020   /* error occurred on this file */
   };

   int _fillbuf(FILE *);
   int _flushbuf(int, FILE *);

   #define feof(p)     ((p)->flag & _EOF) != 0)
   #define ferror(p)   ((p)->flag & _ERR) != 0)
   #define fileno(p)   ((p)->fd)

   #define getc(p)   (--(p)->cnt >= 0 \
                  ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
   #define putc(x,p) (--(p)->cnt >= 0 \
                  ? *(p)->ptr++ = (x) : _flushbuf((x),p))

   #define getchar()   getc(stdin)
   #define putcher(x)  putc((x), stdout)
The getc macro normally decrements the count, advances the pointer, and returns the character. (Recall that a long #define is continued with a backslash.) If the count goes negative, however, getc calls the function _fillbuf to replenish the buffer, re-initialize the structure contents, and return a character. The characters are returned unsigned, which ensures that all characters will be positive.
Although we will not discuss any details, we have included the definition of putc to show that it operates in much the same way as getc, calling a function _flushbuf when its buffer is full. We have also included macros for accessing the error and end-of-file status and the file descriptor.

The function fopen can now be written. Most of fopen is concerned with getting the file opened and positioned at the right place, and setting the flag bits to indicate the proper state. fopen does not allocate any buffer space; this is done by _fillbuf when the file is first read.

   #include <fcntl.h>
   #include "syscalls.h"
   #define PERMS 0666    /* RW for owner, group, others */

   FILE *fopen(char *name, char *mode)
   {
       int fd;
       FILE *fp;

       if (*mode != 'r' && *mode != 'w' && *mode != 'a')
           return NULL;
       for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
           if ((fp->flag & (_READ | _WRITE)) == 0)
               break;        /* found free slot */
       if (fp >= _iob + OPEN_MAX)   /* no free slots */
           return NULL;

       if (*mode == 'w')
           fd = creat(name, PERMS);
       else if (*mode == 'a') {
           if ((fd = open(name, O_WRONLY, 0)) == -1)
               fd = creat(name, PERMS);
           lseek(fd, 0L, 2);
       } else
           fd = open(name, O_RDONLY, 0);
       if (fd == -1)         /* couldn't access name */
           return NULL;
       fp->fd = fd;
       fp->cnt = 0;
       fp->base = NULL;
       fp->flag = (*mode == 'r') ? _READ : _WRITE;
       return fp;
   }
This version of fopen does not handle all of the access mode possibilities of the standard, though adding them would not take much code. In particular, our fopen does not recognize the ``b'' that signals binary access, since that is meaningless on UNIX systems, nor the ``+'' that permits both reading and writing.
The first call to getc for a particular file finds a count of zero, which forces a call of _fillbuf. If _fillbuf finds that the file is not open for reading, it returns EOF immediately. Otherwise, it tries to allocate a buffer (if reading is to be buffered).

Once the buffer is established, _fillbuf calls read to fill it, sets the count and pointers, and returns the character at the beginning of the buffer. Subsequent calls to _fillbuf will find a buffer allocated.

   #include "syscalls.h"

   /* _fillbuf:  allocate and fill input buffer */
   int _fillbuf(FILE *fp)
   {
       int bufsize;

       if ((fp->flag&(_READ|_EOF_ERR)) != _READ)
           return EOF;
       bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
       if (fp->base == NULL)     /* no buffer yet */
           if ((fp->base = (char *) malloc(bufsize)) == NULL)
               return EOF;       /* can't get buffer */
       fp->ptr = fp->base;
       fp->cnt = read(fp->fd, fp->ptr, bufsize);
       if (--fp->cnt < 0) {
           if (fp->cnt == -1)
               fp->flag |= _EOF;
           else
               fp->flag |= _ERR;
           fp->cnt = 0;
           return EOF;
       }
       return (unsigned char) *fp->ptr++;
   }
The only remaining loose end is how everything gets started. The array _iob must be defined and initialized for stdin, stdout and stderr:
   FILE _iob[OPEN_MAX] = {    /* stdin, stdout, stderr */
       { 0, (char *) 0, (char *) 0, _READ, 0 },
       { 0, (char *) 0, (char *) 0, _WRITE, 1 },
       { 0, (char *) 0, (char *) 0, _WRITE, | _UNBUF, 2 }
   };
The initialization of the flag part of the structure shows that stdin is to be read, stdout is to be written, and stderr is to be written unbuffered.

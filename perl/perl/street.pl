#!/bin/perl
while(<DATA>){
	($name, $phone,$address, $birth,$salary ) = split(":", $_);
	print  if /Street/;
}
# 验证的数据可以分为两种：外部的文本使用<>;内部的数据使用__DATA__，然后放入
# while循环中也可以的
__DATA__
Tommy Savage:408–724–0140:1222 Oxbow Court, Sunnyvale,CA 94087:5/19/66:34200
Lesle Kerstin:408–456–1234:4 Harvard Square, Boston, MA 02133:4/22/62:52600
JonDeLoach:408–253–3122:123 Park St., San Jose, CA 94086:7/25/53:85100
Ephram Hardy:293–259–5395:235 Carlton Lane, Joliet, IL 73858:8/12/20:56700
Betty Boop:245–836–8357:635 Cutesy Lane, Hollywood, CA 91464:6/23/23:14500
William Kopf:846–836–2837:6937 Ware Road, Milton, PA 93756:9/21/46:43500
Norma Corder:397–857–2735:74 Pine Street, Dearborn, MI 23874:3/28/45:245700
James Ikeda:834–938–8376:23445 Aster Ave., Allentown, NJ 83745:12/1/38:45000
Lori Gortz:327–832–5728:3465 Mirlo Street, Peabody, MA 34756:10/2/65:35200
Barbara Kerz:385–573–8326:832 Ponce Drive, Gary, IN 83756:12/15/46:268500
###########################
# 1 打印含有Street的行
#while(<DATA>){
#	($name, $phone,$address, $birth,$salary ) = split(":", $_);
#	print  if /Street/;
}
#
#
#
#########################

#!/usr/bin/perl -w
use strict;


my @array = (
['first'   , "a partridge in a pear tree.\n"],
['second'  , "two turtle doves,\nand "      ],
['third'   , "three French hens, "          ],
['fourth'  , "four calling birds, "         ],
['fifth'   , "five golden rings,\n"         ],
['sixth'   , "six geese a-laying, "         ],
['seventh' , "seven swans a-swimming,\n"    ],
['eighth'  , "eight maids a-milking, "      ],
['ninth'   , "nine ladies dancing, "        ],
['tenth'   , "ten lords a leaping,\n"       ],
['eleventh', "eleven pipers piping, "       ],
['twelfth' , "twelve drummers drumming, "   ]
);


print
"On the $array[$_]->[0] day of Christmas my true love gave to me\n".
join('', map { $array[$_]->[1] } reverse 0..$_)
."\n"
for 0..$#array;


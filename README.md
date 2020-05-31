# a-foenix

Outside whatever comes included with int the c library of the WDC compiler there are very few C libraries for the Foenix at the moment. So I either write one myself or use the excelent work of others preventing me from reinventing the wheel. After looking around I thought that porting parts of the old Allegro 4 branch would be the way to go. That branch still supports dos, which is an OS that does most things thru direct hardware access which makes it a nice fit for a platform doing the same. 

For the moment I only got the keyboard routines in a state that could be called working. I will just bolt on parts as I see fit. 

I have not choosen to integrate with the original source as Allegro 4 is not longer developed. I did not use the Version 5 branch as it dropped MSDOS support which I am basing things off. Allegro developers state that they would accept patches for version 4, but supporting a platform that only exists for about 50 users would hardly qualify.

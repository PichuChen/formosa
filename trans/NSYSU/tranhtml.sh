#!/bin/csh
#
# National Sun Yat-sen
#

foreach file (*.html)

	foreach tok ("��ߤ��s�j�ǡ@���R���q" "���s�j��")
		sed -e 's/'$tok'/'@BBS_CNAME@'/g' $file > $file.tmp
		mv $file.tmp $file
	end

	set tok="bbs.nsysu.edu.tw"
	sed -e 's/'$tok'/'@BBS_DOMAIN@'/g' $file > $file.tmp
	mv $file.tmp $file

	set tok="Formosa"
	sed -e 's/'$tok'/'@BBS_ID@'/g' $file > $file.tmp
	mv $file.tmp $file
end

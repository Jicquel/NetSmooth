#!/bin/bash
list=$(ls /var/lib/lxc/)

if [ "$1" = "clean" ]; then
	for i in $list; do
		if [ "$UID" -ne "0" ]; then
			path="~/.local/share/lxc/$i/rootfs"
		else
			path="/var/lib/lxc/$i/rootfs"
		fi
		rm -rf $path/.scr
		rm -rf $path/.networkInfo
		cp $path/etc/.bash.bashrc $path/etc/bash.bashrc
	done
	echo "container cleaned."
else
	for i in $list; do
		path="/var/lib/lxc/$i/rootfs"

		if ! [ -e $path/etc/.bash.bashrc ]; then
			cp $path/etc/bash.bashrc $path/etc/.bash.bashrc
		fi
		mkdir $path/.networkInfo

		#
		# .bashrc
		#
		echo "alias ls='ls --color'" >> $path/etc/bash.bashrc
		echo "alias grep='grep --color'" >> $path/etc/bash.bashrc
		echo "alias route='/.scr/aliasRoute.sh'" >> $path/etc/bash.bashrc
		echo "alias ifconfig='/.scr/aliasIfconfig.sh'" >> $path/etc/bash.bashrc
		echo "alias ip='/.scr/aliasIp.sh'" >> $path/etc/bash.bashrc
		echo "/.scr/majIpconfig.sh" >> $path/etc/bash.bashrc
		echo "/.scr/majRoute4Config.sh" >> $path/etc/bash.bashrc
		echo "/.scr/majRoute6Config.sh" >> $path/etc/bash.bashrc

		#
		# .vimrc
		#
		echo "set nu" > $path/root/.vimrc
		echo "syn on" >> $path/root/.vimrc
		echo "set autoindent" >> $path/root/.vimrc
		echo "set smartindent" >> $path/root/.vimrc
		echo "set scrolloff=5" >> $path/root/.vimrc
		echo "set showcmd" >> $path/root/.vimrc
		echo "set incsearch" >> $path/root/.vimrc
		echo "colorscheme darkblue" >> $path/root/.vimrc

		mkdir $path/.scr
		path="$path/.scr"

		#
		# aliasIp
		#
		echo "#!/bin/bash" >> $path/aliasIp.sh
		echo "list=\$@" >> $path/aliasIp.sh
		echo "if [ \"\$(expr match \"\$list\" '.*-6')\" != \"0\" ] && [ \"\$(expr match \"\$list\" '.*:')\" != \"0\" ]; then" >> $path/aliasIp.sh
		echo "	a=\$(echo \$(expr match \"\$list\" '.*eth'))" >> $path/aliasIp.sh
		echo "	interface=eth\${list:a:1}" >> $path/aliasIp.sh
		echo "	ipv6=\$(ifconfig \$interface | grep 'inet6' | sed 's/^.*inet6[^0-9a-f]*\\([0-9a-f:]*\\).*\$/\1/' )" >> $path/aliasIp.sh
		echo "	if [ \"\$ipv6\" != \"\" ]; then" >> $path/aliasIp.sh
		echo "		ifconfig \$interface del \$ipv6" >> $path/aliasIp.sh
		echo "	fi" >> $path/aliasIp.sh
		echo "fi" >> $path/aliasIp.sh
		echo "ip \$@" >> $path/aliasIp.sh
		echo "/.scr/majIpconfig.sh" >> $path/aliasIp.sh
		echo "/.scr/majRoute4Config.sh" >> $path/aliasIp.sh
		echo "/.scr/majRoute6Config.sh" >> $path/aliasIp.sh

		#
		# aliasIpconfig
		#
		echo "#!/bin/bash" >> $path/aliasIfconfig.sh
		echo "list=\$@" >> $path/aliasIfconfig.sh
		echo "if [ \"\$(expr match \"\$list\" '.*add')\" != \"0\" ] && [ \"\$(expr match \"\$list\" '.*:')\" != \"0\" ]; then" >> $path/aliasIfconfig.sh
		echo "	a=\$(echo \$(expr match \"\$list\" '.*eth'))" >> $path/aliasIfconfig.sh
		echo "	interface=eth\${list:a:1}" >> $path/aliasIfconfig.sh
		echo "	ipv6=\$(ifconfig \$interface | grep 'inet6' | sed 's/^.*inet6\\([^0-9a-f]*[0-9a-f:/]*\\).*\$/\1/' )" >> $path/aliasIfconfig.sh
		echo "if [ \"\$(echo \$ipv6 | grep '/')\" = \"\" ]; then" >> $path/aliasIfconfig.sh
		echo "	ipv6=\"\$ipv6\$(/sbin/ifconfig \$interface | grep 'inet6' | sed 's/^.*prefixlen[^0-9]*\\([0-9]*\\).*\$/\1/'))" >> $path/aliasIfconfig.sh
		echo "	fi" >> $path/aliasIfconfig.sh
		echo "	if [ \"\$ipv6\" != \"\" ]; then" >> $path/aliasIfconfig.sh
		echo "		ifconfig \$interface del \$ipv6" >> $path/aliasIfconfig.sh
		echo "	fi" >> $path/aliasIfconfig.sh
		echo "fi" >> $path/aliasIfconfig.sh
		echo "ifconfig \$@" >> $path/aliasIfconfig.sh
		echo "/.scr/majIpconfig.sh" >> $path/aliasIfconfig.sh

		#
		# aliasRoute
		#
		echo "#!/bin/bash" > $path/aliasRoute.sh
		echo "route -n \$@" >> $path/aliasRoute.sh
		echo "/.scr/majRoute4Config.sh" >> $path/aliasRoute.sh
		echo "/.scr/majRoute6Config.sh" >> $path/aliasRoute.sh

		#
		# majRoute4
		#
		echo "#!/bin/bash" >> $path/majRoute4Config.sh
		echo "listDest=\$(route -n | grep 'eth' | awk {'print \$1'})" >> $path/majRoute4Config.sh
		echo "listGw=\$(route -n | grep 'eth' | awk {'print \$2'})" >> $path/majRoute4Config.sh
		echo "listMask=\$(route -n | grep 'eth' | awk {'print \$3'})" >> $path/majRoute4Config.sh
		echo "listIface=\$(route -n | grep 'eth' | awk {'print \$8'})" >> $path/majRoute4Config.sh
		echo "list=(\$listIface)" >> $path/majRoute4Config.sh
		echo "echo -n > /.networkInfo/route4Config.info" >> $path/majRoute4Config.sh
		echo "i=0" >> $path/majRoute4Config.sh
		echo "while [ \$i -lt \${#list[@]} ]; do" >> $path/majRoute4Config.sh
		echo "	echo \"\$listIface\" | sed \$((i+1))'!d' >> /.networkInfo/route4Config.info" >> $path/majRoute4Config.sh
		echo "	echo \"\$listDest\" | sed \$((i+1))'!d' >> /.networkInfo/route4Config.info" >> $path/majRoute4Config.sh
		echo "	echo \"\$listGw\" | sed \$((i+1))'!d' >> /.networkInfo/route4Config.info" >> $path/majRoute4Config.sh
		echo "	echo \"\$listMask\" | sed \$((i+1))'!d' >> /.networkInfo/route4Config.info" >> $path/majRoute4Config.sh
		echo "	i=\$((i+1))" >> $path/majRoute4Config.sh
		echo "done" >> $path/majRoute4Config.sh

		#
		# majRoute6
		#
		echo "#!/bin/bash" >> $path/majRoute6Config.sh
		echo "listDest=\$(route -6 | grep 'eth' | awk {'print \$1'})" >> $path/majRoute6Config.sh
		echo "listGw=\$(route -6 | grep 'eth' | awk {'print \$2'})" >> $path/majRoute6Config.sh
		echo "listIface=\$(route -6 | grep 'eth' | awk {'print \$7'})" >> $path/majRoute6Config.sh
		echo "listDest=(\$listDest)" >> $path/majRoute6Config.sh
		echo "listGw=(\$listGw)" >> $path/majRoute6Config.sh
		echo "listIface=(\$listIface)" >> $path/majRoute6Config.sh
		echo "echo -n > /.networkInfo/route6Config.info" >> $path/majRoute6Config.sh
		echo "i=0" >> $path/majRoute6Config.sh
		echo "while [ \$i -lt \${#listDest[@]} ]; do" >> $path/majRoute6Config.sh
		echo "	echo \${listDest[\$i]} >> /.networkInfo/route6Config.info" >> $path/majRoute6Config.sh
		echo "	echo \${listGw[\$i]} >> /.networkInfo/route6Config.info" >> $path/majRoute6Config.sh
		echo "	echo \${listIface[\$i]} >> /.networkInfo/route6Config.info" >> $path/majRoute6Config.sh
		echo "	i=\$((i+1))" >> $path/majRoute6Config.sh
		echo "done" >> $path/majRoute6Config.sh

		#
		# majIp
		#
		echo "#!/bin/bash" > $path/majIpconfig.sh
		echo "echo -n > /.networkInfo/ipConfig.info" >> $path/majIpconfig.sh
		echo "listIfaces=\$(ls /sys/class/net)" >> $path/majIpconfig.sh
		echo "for iface in \$listIfaces; do" >> $path/majIpconfig.sh
		echo "	echo \$iface >> /.networkInfo/ipConfig.info	#interface" >> $path/majIpconfig.sh
		echo "	echo \$(ifconfig \$iface | grep -w inet | sed 's/^.*inet[^0-9]*\\([0-9.]*\\).*\$/\1/') >> /.networkInfo/ipConfig.info	#ipv4" >> $path/majIpconfig.sh
		echo "	echo \$(ifconfig \$iface | grep -w inet | sed 's/^.*netmask[^0-9]*\\([0-9.]*\\).*\$/\1/') >> /.networkInfo/ipConfig.info	#mask" >> $path/majIpconfig.sh
			
		echo "	ipv6=\$(/sbin/ifconfig \$interface | grep 'inet6' | sed 's/^.*inet6[^0-9a-f]*\\([0-9a-f:/]*\\).*\$/\1/' )" >> $path/majIpconfig.sh
		echo "	if [ \"\$(echo \$ipv6 | grep '/')\" = \"\" ]; then" >> $path/majIpconfig.sh
		echo "		ipv6=\"\$ipv6\$(/sbin/ifconfig \$interface | grep 'inet6' | sed 's/^.*prefixlen[^0-9]*\\([0-9]*\\).*\$/\1/'))" >> $path/majIpconfig.sh
		echo "	fi" >> $path/majIpconfig.sh
	
		echo "	echo \$ipv6 >> /.networkInfo/ipConfig.info	#ipv6" >> $path/majIpconfig.sh
		
		echo "done" >> $path/majIpconfig.sh

		#
		# reinitConfig
		#
		echo "#!/bin/bash" > $path/reinitConfig.sh
		echo "for a in \$(ls /.networkInfo); do" >> $path/reinitConfig.sh
		echo "	echo -n > /.networkInfo/\$a" >> $path/reinitConfig.sh
		echo "done" >> $path/reinitConfig.sh

		chmod 775 $path/*.sh
	done
fi

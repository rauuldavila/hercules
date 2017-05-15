apt-get install openssh-server
sed -i 's/Port.*/Port 2222/' /etc/ssh/sshd_config
/etc/init.d/ssh restart

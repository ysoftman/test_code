#!/bin/bash
apr_version="1.6.5"
apr_util_version="1.6.1"
httpd_version="2.4.38"
dest_dir="/home/ysoftman"
yum --version
if [ $? == 0 ]; then
    package_program="yum -y"
    packages="expat-devel pcre-devel zlib-devel libxml2-devel openldap-devel openssl-devel"
else
    package_program="apt-get -y --fix-missing"
    packages="libexpat-dev libpcre3 libz-dev libxml2-dev libldap2-dev libssl-dev"
fi
echo "package_program ${package_program}"

# 리눅스용 Apache Httpd 설치전 필요한 프로그램 설치
sudo ${package_program} install ${packages}

# install apr
cd ${dest_dir}
wget http://apache.mirror.cdnetworks.com/apr/apr-${apr_version}.tar.gz
tar zxvf apr-${apr_version}.tar.gz
cd apr-${apr_version}
./configure --prefix=${dest_dir}/apr
make -j 4 && make install


# install apr-util
cd ${dest_dir}
wget http://apache.mirror.cdnetworks.com/apr/apr-util-${apr_util_version}.tar.gz
tar zxvf apr-util-${apr_util_version}.tar.gz
cd apr-util-${apr_util_version}
./configure --prefix=${dest_dir}/apr-util --with-apr=${dest_dir}/apr
make -j 4 && make install


# install apache http 2.4
cd ${dest_dir}
wget http://apache.mirror.cdnetworks.com/httpd/httpd-${httpd_version}.tar.gz
tar zxvf httpd-${httpd_version}.tar.gz
cd httpd-${httpd_version}
# prefix 를 명시하지 않으면 디폴트는 /usr/local/apache2
./configure --prefix=${dest_dir}/httpd --with-apr=${dest_dir}/apr --with-apr-util=${dest_dir}/apr-util --with-mpm=prefork --enable-mods-shared="rewrite alias dir"
make -j 4 && make install


# copy httpd.conf and run httpd
# cp -v ./httpd.conf ${dest_dir}/httpd/conf
# ${dest_dir}/httpd/bin/apachectl start


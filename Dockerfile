FROM centos:7

RUN \
  yum -y install openssh-clients openssh-server && \
  yum -y clean all && \
  touch /run/utmp && \
  chmod u+s /usr/bin/ping && \
  echo "root:root" | chpasswd

RUN yum install -y centos-release-scl
RUN yum install -y devtoolset-7-gcc*
RUN yum install -y make
RUN yum install -y epel-release
RUN yum install -y cmake3
RUN yum install -y rpm-build
RUN echo "source /opt/rh/devtoolset-7/enable" >> ~/.bash_profile

COPY entrypoint.sh /
COPY flm_source /flm_source
COPY flm_rpm /flm_rpm
RUN yum install -y /flm_rpm/flm-1.0-1.el7.x86_64.rpm
COPY auxiliary/flm_run.sh /usr/local/bin
RUN mkdir /workdir
RUN chmod -R 777 /workdir


EXPOSE 22
ENTRYPOINT ["/entrypoint.sh"]
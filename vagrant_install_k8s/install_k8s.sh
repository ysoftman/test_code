#!/bin/bash
echo "----- install kubernetes -----"
echo "whoami:" $(whoami)
custom_eth=${1}
node_name=${2}
echo ${custom_eth}
echo ${node_name}

# apt 저장소 추가
# 참고 https://kubernetes.io/ko/docs/setup/production-environment/tools/kubeadm/install-kubeadm/
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update

# k8s 설치
apt-cache madison kubeadm | grep 1.19
k8s_version="1.19.16-00"
sudo apt-get install -y kubelet=${k8s_version} kubeadm=${k8s_version} kubectl=${k8s_version}
# kubelet kubeadm kubectl 업데이트 되지 않도록 hold 설정
sudo apt-mark hold kubelet kubeadm kubectl

# vagrant 환경에서 eth0 ip 는  NAT 로 모든 노드가 같은 IP 로 되어 있다.
# 따라서 k8s 설치에는 eth1 ip(192.168.100.2) 를 사용하도록 설정한다.
if [[ ${custom_eth} != "" ]]; then
    IP_ADDR=$(ifconfig ${custom_eth} | grep netmask | awk '{print $2}')
    echo "KUBELET_EXTRA_ARGS=--node-ip=\"$IP_ADDR\"" | sudo tee /etc/default/kubelet
    sudo systemctl restart kubelet
fi

if [[ ${node_name} =~ ^master.* ]]; then
    echo "----- master node -----"
    # master 노드에서 kubeadm 으로 클러스터를 구성한다.
    sudo kubeadm init \
    --apiserver-advertise-address=192.168.100.2 \
    --apiserver-cert-extra-sans=192.168.100.2 \
    --node-name=${node_name} \
    --pod-network-cidr=10.224.0.0/16 \
    --service-cidr=10.225.0.0/16 | tee /vagrant/kubeadm_stdout.tmp.txt

    # kubectl 사용을 위한 kubeconfig 설정
    mkdir -p $HOME/.kube
    sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    sudo chown $(id -u):$(id -g) $HOME/.kube/config

    # flannel 설치
    rm -rf kube-flannel.tmp.yml
    wget https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.tmp.yml
    # net-conf.json -> network ip 변경
    # eth1 사용하는것으로 yml 설정 변경
    sed -i -e 's/Network": "10.244.0.0\/16/Network": "10.224.0.0\/16/' \
    -e '/--kube-subnet-mgr/{a\
        - --iface=eth1
}' kube-flannel.tmp.yml
    # flannel 적용
    kubectl apply -f kube-flannel.tmp.yml
fi

if [[ ${node_name} =~ ^worker.* ]]; then
    echo "----- worker node -----"
    # worker --> master 로 조인
    bash -c "sudo $(cat /vagrant/kubeadm_stdout.tmp.txt | grep "kubeadm join" -A 1)"
fi

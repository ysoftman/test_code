# vagrant 에서 kubernetes 설치

```bash
# vagrant 실행시 install_k8s.sh 로 kubernetes 설치
vagrant up

# master 노드 접속해서 k8s 확인
vagrant ssh control-plane

# 노드 확인
kubectl get nodes
kubectl describe nodes control-plane
kubectl get nodes control-plane -o yaml

# namespace 확인
kubectl get ns

# pod 확인
kubectl get pods -A -o wide

# pod log 확인
NAMESPACE="kube-system"
POD=$(kubectl get pods -A | grep -i kube-api | awk '{print $2}')
kubectl logs -f ${POD} -n ${NAMESPACE}

# configmap 확인
kubectl get configmap kubeadm-config -n kube-system -o yaml

# cluster 정보 확인
kubectl cluster-info
kubectl cluster-info dump

# 서비스 확인
kubectl get services -A
# 서비스 ip 443 포트 통신 확인
nc -v 10.225.0.1 443

# socket -p(print) -l(listening) -n(numeric, do not try to resolve service names) -t(tcp) 확인
sudo ss -plnt

# route -n (numerical address) 확인
sudo route -n

# iptables 확인
sudo iptables -t nat -S
sudo iptables -t filter -S

# etcd 명세 확인
sudo cat /etc/kubernetes/manifests/etcd.yaml

# 별도 터미널에서 pod watching 으로 상태 모니터링 해두고
kubectl get pods -w

# pod 띄우기 (exit 하면 pod 종료)
kubectl run -i --tty --image busybox:1.28 ysoftman-test --restart=Never --rm /bin/sh
# pod 에서 --> 외부로 ping 해보기
ping 8.8.8.8
```

# k8s test

## kubernetes(k8s) 관련 테스트

```bash
kubectl delete -f ysoftman-pod-test.yaml; kubectl apply -f ysoftman-pod-test.yaml
kubectl apply -f ysoftman-cronjob-test.yaml
```

## k8s 정보 파악 스크립트

```bash
# node 별 디스크 사용량 파악 스크립트
bash ./get_node_disk_usage.sh
# pod/container 별 디스크 사용량 파악 스크립트
bash ./get_container_disk_usage.sh
```

## ingress-nginx-controller 설치된 상태에서 ingress admission 기능이 없을때 추가

- 자세한 설명 <https://yoonbh2714.blogspot.com/2021/12/k8s-validatingwebhookconfiguration.html>

```bash
# ValidatingWebhookConfiguration 은 TLS 로 통신해야 한다.
# 다음과 같이 self-singed 로 키를 생성한다.
# service 에서 사용할 이름이 매칭될 수 있도록 CN을 다음과 같이 설정한다. (CN=${SERVICE_NAME}.${NAMESPACE}.svc)
openssl req -x509 -newkey rsa:2048 -keyout validating-webhook-key.pem -out validating-webhook-cert.pem -days 100000 -nodes -subj "/CN=ingress-nginx-controller-admission.ingress-nginx.svc"

# secret 리소스를 등록하자.(base64 인코딩돼 등록되기 때문에 secrete 리소스를 보면 LS0... 으로 시작하는 문자열이 된다.)
kubectl create secret tls ingress-validation-tls -n ingress-nginx \
--key validating-webhook-key.pem \
--cert validating-webhook-cert.pem

# 등록
# 참고로 base64 인코딩하면 시작과 끝부분의 ---BEGIN.. ----END.. 없이 LS0... 으로 시작하는 문자열이 된다.
CA_BUNDLE=$(cat validating-webhook-cert.pem | base64)
cat ingress_admission.yaml | sed "s/\${CA_BUNDLE}/${CA_BUNDLE}/" | kubectl apply -f -

# nginx 문법에러가 있는 ingress 리소스 등록시 admission 에서 탐지되어 리소스로 등록되면 안된다.
kubectl apply -f syntax_error_ingress.yaml
```

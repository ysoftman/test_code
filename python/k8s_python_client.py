# pip install kubernetes
import os

from kubernetes import client, config


class color:
    default = "\033[0m"
    black = "\033[0;30m"
    red = "\033[0;31m"
    green = "\033[0;32m"
    yellow = "\033[0;33m"
    blue = "\033[0;34m"
    magenta = "\033[0;35m"
    cyan = "\033[0;36m"
    white = "\033[0;37m"


# KUBECONFIG 환경 변수 사용 없으면, default: ~/.kube/config
cfgfile = os.environ.get("KUBECONFIG", "~/.kube/config")
print(cfgfile)
config.load_kube_config(cfgfile)

v1 = client.CoreV1Api()
ns = v1.list_pod_for_all_namespaces(watch=False)
for item in ns.items:
    print(
        f"{color.green}{item.status.pod_ip}, {color.yellow}{item.metadata.namespace}, {color.blue}{item.metadata.name}{color.default}"
    )

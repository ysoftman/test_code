## ansible 테스트
```bash
ansible -i ./inventory testhost1 -u hanadmin -m command -a "ls -ahl"
```

## ansible-playbook 테스트
```bash
ansible-playbook -i ./inventory myplaybook.yml -t clearall -vv

ansible-playbook -i ./inventory myplaybook.yml -t helloworld -vv

# --connection=local 플레이북 작업을 로컬에서 수행한다.
ansible-playbook -i ./inventory myplaybook.yml -t helloworld -vv --connection=local

ansible-playbook -i ./inventory myplaybook.yml -t mylocation -vv

ansible-playbook -i ./inventory myplaybook.yml -t myname -vv

ansible-playbook -i ./inventory myplaybook.yml -t print_debug -vv
```
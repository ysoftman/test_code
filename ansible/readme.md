## ansible 테스트
```bash
ansible -i host testhost1 -u hanadmin -m command -a "ls -ahl"
```

## ansible-playbook 테스트
```bash
ansible-playbook -i host myplaybook.yml -t clearall -vv

ansible-playbook -i host myplaybook.yml -t helloworld -vv

ansible-playbook -i host myplaybook.yml -t mylocation -vv

ansible-playbook -i host myplaybook.yml -t myname -vv

ansible-playbook -i host myplaybook.yml -t print_debug -vv
```
# ansible 테스트

```bash
ansible -i ./inventory testhost1 -u ysoftman -m command -a "ls -ahl"
```

## ansible-playbook 테스트

### myplaybook.yml

```bash
# 적용될 task, tag 파악
ansible-playbook -i ./inventory myplaybook.yml -vv --list-tasks --list-tags

ansible-playbook -i ./inventory myplaybook.yml -t clearall -vv

ansible-playbook -i ./inventory myplaybook.yml -t helloworld -vv

# --connection=local 플레이북 작업을 로컬에서 수행한다.
ansible-playbook -i ./inventory myplaybook.yml -t helloworld -vv --connection=local

ansible-playbook -i ./inventory myplaybook.yml -t helloworld,print_debug -e "edit_file=yes" -vv --connection=local

ansible-playbook -i ./inventory myplaybook.yml -t mylocation -vv

ansible-playbook -i ./inventory myplaybook.yml -t myname -vv

ansible-playbook -i ./inventory myplaybook.yml -t print_debug -vv
```

### myplaybook2.yml

```bash
ansible-playbook -i ./inventory -l localhost myplaybook2.yml -vv  --connection=local -t my_role1 -e task_num=1

ansible-playbook -i ./inventory -l localhost myplaybook2.yml -vv  --connection=local -t my_role2 -e task_num=1

ansible-playbook -i ./inventory -l localhost myplaybook2.yml -vv  --connection=local -t my_role3 -e service_env=production
```

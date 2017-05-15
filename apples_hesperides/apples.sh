ssh-keygen -t rsa
cat ~/.ssh/test_key.pub | ssh rdavila@$VM_IP "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"

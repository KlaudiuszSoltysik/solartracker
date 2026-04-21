- argo workflows
- argo events
- tests
- terraform
- vpn?
- cloudflare
- resources
- prod enviorment + dev edit
- keycloak
- mobile app

# Usefull commands:
kubectl create secret generic ai-agent-creds \
  --from-literal=github-token=token \
  -n ai-agent \
  --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/base/ai-agent/secret.yml

rm raw-secret.yml
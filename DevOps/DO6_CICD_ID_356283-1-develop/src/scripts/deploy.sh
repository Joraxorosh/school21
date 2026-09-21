#!/usr/bin/env bash
# Copies built binaries to the production VM's /usr/local/bin over scp/ssh.
# Usage: deploy.sh <binary1> [binary2 ...]
# Requires DEPLOY_HOST, DEPLOY_USER (set in the runner's own config.toml
# environment). The gitlab-runner system user's default SSH key
# (~/.ssh/id_ed25519) is used for auth — its public half is already in
# DEPLOY_USER@DEPLOY_HOST:~/.ssh/authorized_keys.

set -euo pipefail

: "${DEPLOY_HOST:?DEPLOY_HOST is not set}"
: "${DEPLOY_USER:?DEPLOY_USER is not set}"

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 <binary> [binary...]"
  exit 1
fi

mkdir -p ~/.ssh
chmod 700 ~/.ssh

ssh-keyscan -H "$DEPLOY_HOST" >> ~/.ssh/known_hosts 2>/dev/null

for BIN in "$@"; do
  echo "==> copying $BIN to ${DEPLOY_USER}@${DEPLOY_HOST}:/usr/local/bin/"
  scp -o StrictHostKeyChecking=yes "$BIN" "${DEPLOY_USER}@${DEPLOY_HOST}:/usr/local/bin/"
  ssh -o StrictHostKeyChecking=yes "${DEPLOY_USER}@${DEPLOY_HOST}" \
    "chmod +x /usr/local/bin/$(basename "$BIN")"
done

echo "Deploy OK: $* -> ${DEPLOY_USER}@${DEPLOY_HOST}:/usr/local/bin"

# Module: Port-Forwarder

## Purpose:
This script is designed to forward a specified service (TimescaleDB) and its associated services (MongoDB, RabbitMQ, ArgoCD, Prometheus, Grafana, Ollama, Backend API) to the same external IP address. The script uses Kubernetes' `kubectl` command-line tool to perform port forwarding.

## Files:
- `../scripts/port-forwarder.sh`: Contains the main script for executing the port forwarding commands.
  - `cleanup() { ... }`: A function that cleans up any existing jobs and exits with status code 0 if no jobs are left.
  - `trap cleanup SIGINT SIGTERM`: Traps the `SIGINT` (Ctrl+C) and `SIGTERM` signals to clean up any remaining jobs.
- `kubectl port-forward svc/timescaledb 5432:5432 > /dev/null 2>&1 &`: Forwarding service "timescaledb" to the external IP address 5432. The command redirects the traffic from the specified service to the external IP address.

## Usage:
To use this script, save it in a directory of your choice and run it with `./port-forwarder.sh`.

### Example:
```bash
chmod +x ../scripts/port-forwarder.sh
./port-forwarder.sh
```

This will forward all traffic from "timescaledb" to the external IP address 5432.
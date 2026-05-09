# RabbitMQ CronJob

This is a cron job that runs every minute to ensure RabbitMQ services are running and up-to-date.

## Configuration

- **RabbitMQ Host**: `rabbitmq`
  - **Port**: `5672`
  - **Username**: `admin`
  - **Password**: `admin`

- **RabbitMQ Username**: `timescaledb`
  - **Host**: `rabbitmq`
  - **Port**: `5432`
  - **Database**: `default_db`

## Deployment

This deployment uses a RabbitMQ instance to host the Telemetry Processor service.

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: telemetry-processor
  namespace: default
spec:
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: telemetry-processor
  template:
    metadata:
      labels:
        app: telemetry-processor
    spec:
      enableServiceLinks: false
      imagePullSecrets:
      - name: ghcr-secret
      containers:
      - name: telemetry-processor
        image: telemetry-processor
        imagePullPolicy: Always
        env:
        - name: RABBITMQ_HOST
          value: "rabbitmq"
        - name: RABBITMQ_PORT
          value: "5672"
        - name: RABBITMQ_USERNAME
          valueFrom:
            secretKeyRef:
              name: rabbitmq-creds
              key: username
        - name: RABBITMQ_PASSWORD
          valueFrom:
            secretKeyRef:
              name: rabbitmq-creds
              key: password
```

## StatefulSet

This stateful set uses a RabbitMQ instance to host the Timescaledb service.

```yaml
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: timescaledb
  namespace: default
spec:
  serviceName: "timescaledb"
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: timescaledb
  template:
    metadata:
      labels:
        app: timescaledb
    spec:
      containers:
      - name: timescaledb
        image: timescale/timescaledb:latest-pg16
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_USER
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
        - name: POSTGRES_DB
          value: "default_db"
        ports:
        - containerPort: 5432
        volumeMounts:
        - name: init-scripts
          mountPath: /docker-entrypoint-initdb.d/
        - name: timescaledb-data
          mountPath: /var/lib/postgresql/data 
      volumes:
      - name: init-scripts
        configMap:
          name: timescaledb-init-scripts
```

## ConfigMap

This configuration map contains the RabbitMQ credentials and secret.

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: timescaledb-creds
  namespace: default
data:
  username: admin
  password: admin
  host: rabbitmq
  port: 5432
  database: default_db
```

## Monitoring

You can monitor the RabbitMQ and Timescaledb services using tools like Prometheus or Grafana.

```yaml
apiVersion: monitoring.coreos.com/v1
kind: ServiceMonitor
metadata:
  name: rabbitmq-monitor
  namespace: default
spec:
  service:
    name: rabbitmq
    port: 5672
```

## Deployment

You can deploy the RabbitMQ and Timescaledb services using Helm charts.

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: rabbitmq
  namespace: default
spec:
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: rabbitmq
  template:
    metadata:
      labels:
        app: rabbitmq
    spec:
      enableServiceLinks: false
      imagePullSecrets:
      - name: ghcr-secret
      containers:
      - name: rabbitmq
        image: rabbitmq:4-management-alpine
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_HOST
          value: "timescaledb"
        - name: POSTGRES_PORT
          value: "5432"
        - name: POSTGRES_USERNAME
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
```

```yaml
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: timescaledb
  namespace: default
spec:
  serviceName: "timescaledb"
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: timescaledb
  template:
    metadata:
      labels:
        app: timescaledb
    spec:
      containers:
      - name: timescaledb
        image: timescale/timescaledb:latest-pg16
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_USER
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
```

## ConfigMap

You can create a configuration map to store the RabbitMQ credentials and secrets.

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: rabbitmq-creds
  namespace: default
data:
  username: admin
  password: admin
  host: rabbitmq
  port: 5432
  database: default_db
```

## Monitoring

You can monitor the RabbitMQ and Timescaledb services using tools like Prometheus or Grafana.

```yaml
apiVersion: monitoring.coreos.com/v1
kind: ServiceMonitor
metadata:
  name: rabbitmq-monitor
  namespace: default
spec:
  service:
    name: rabbitmq
    port: 5672
```

## Deployment

You can deploy the RabbitMQ and Timescaledb services using Helm charts.

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: rabbitmq
  namespace: default
spec:
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: rabbitmq
  template:
    metadata:
      labels:
        app: rabbitmq
    spec:
      enableServiceLinks: false
      imagePullSecrets:
      - name: ghcr-secret
      containers:
      - name: rabbitmq
        image: rabbitmq:4-management-alpine
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_HOST
          value: "timescaledb"
        - name: POSTGRES_PORT
          value: "5432"
        - name: POSTGRES_USERNAME
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
```

```yaml
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: timescaledb
  namespace: default
spec:
  serviceName: "timescaledb"
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: timescaledb
  template:
    metadata:
      labels:
        app: timescaledb
    spec:
      containers:
      - name: timescaledb
        image: timescale/timescaledb:latest-pg16
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_USER
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
```

## ConfigMap

You can create a configuration map to store the RabbitMQ credentials and secrets.

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: timescaledb-creds
  namespace: default
data:
  username: admin
  password: admin
  host: rabbitmq
  port: 5432
  database: default_db
```

## Monitoring

You can monitor the RabbitMQ and Timescaledb services using tools like Prometheus or Grafana.

```yaml
apiVersion: monitoring.coreos.com/v1
kind: ServiceMonitor
metadata:
  name: rabbitmq-monitor
  namespace: default
spec:
  service:
    name: rabbitmq
    port: 5672
```

## Deployment

You can deploy the RabbitMQ and Timescaledb services using Helm charts.

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: rabbitmq
  namespace: default
spec:
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: rabbitmq
  template:
    metadata:
      labels:
        app: rabbitmq
    spec:
      enableServiceLinks: false
      imagePullSecrets:
      - name: ghcr-secret
      containers:
      - name: rabbitmq
        image: rabbitmq:4-management-alpine
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_HOST
          value: "timescaledb"
        - name: POSTGRES_PORT
          value: "5432"
        - name: POSTGRES_USERNAME
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
```

```yaml
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: timescaledb
  namespace: default
spec:
  serviceName: "timescaledb"
  replicas: 1
  revisionHistoryLimit: 1
  selector:
    matchLabels:
      app: timescaledb
  template:
    metadata:
      labels:
        app: timescaledb
    spec:
      containers:
      - name: timescaledb
        image: timescale/timescaledb:latest-pg16
        imagePullPolicy: IfNotPresent
        env:
        - name: POSTGRES_USER
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: username
        - name: POSTGRES_PASSWORD
          valueFrom:
            secretKeyRef:
              name: timescaledb-creds
              key: password
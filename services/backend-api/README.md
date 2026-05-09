# Services Backend-Api

## Overview

This is a Python-based FastAPI application designed to handle WebSocket communication and API endpoints for managing telemetry data from solar trackers. The application uses RabbitMQ for message processing and PostgreSQL for database operations.

### Key Features:

1. **WebSocket Communication:**
   - Implement WebSocket support using FastAPI.
   - Handle incoming WebSocket connections, broadcasting messages to all connected clients.

2. **Database Operations:**
   - Use MongoDB for storing telemetry data.
   - Connect to a PostgreSQL database for real-time analytics and asset management.

3. **Authentication:**
   - Utilize JWT for user authentication and authorization.
   - Implement OAuth 2.0 for secure token exchange.

4. **Error Handling:**
   - Handle WebSocket disconnections, errors, and exceptions using try-except blocks.

5. **API Endpoints:**
   - `/api/v1/telemetry/{device_id}`: Fetch telemetry data from a specific device.
   - `/api/v1/energy-forecast/{device_id}`: Fetch energy forecast data for a specific device.
   - `/api/v1/assets`: Retrieve assets information, including PV and wind assets.

### Technical Architecture

The application is built using the following components:

1. **FastAPI:** A microframework for building web applications with Python.
2. **RabbitMQ:** For message processing and real-time data exchange.
3. **PostgreSQL:** For storing telemetry data and managing asset information.
4. **MongoDB:** For real-time analytics and asset management.

### Usage

To use this application, you need to install the required libraries:

```bash
pip install fastapi uvicorn rabbitmq_management psycopg2 pymongo
```

You can start the development server by running:

```bash
uvicorn main:app --host 0.0.0.0 --port 8001
```

### Deployment

This application is deployed on Heroku, which you can access at [heroku](https://devcenter.heroku.com/articles/heroku-postgres).

## Setup Instructions

Before starting the development process:

- Ensure you have Python installed.
- Install the required libraries using pip:
  ```bash
  pip install fastapi uvicorn rabbitmq_management psycopg2 pymongo
  ```

- Clone this repository and navigate to the project directory:
  ```bash
  git clone https://github.com/yourusername/solar-tracking-app.git
  cd solar-tracking-app
  ```

- Install dependencies:
  ```bash
  pip install .
  ```

- Start the development server:
  ```bash
  uvicorn main:app --host 0.0.0.0 --port 8001
  ```

## Running Tests

To run unit tests and integration tests:

```bash
python -m unittest discover
```

You can also use a testing framework like `pytest` for more complex scenarios.

## Contributing

Contributions are welcome! If you want to contribute, please follow these guidelines:

- Make sure your changes are documented.
- Add tests for new features and bug fixes.
- Follow the coding standards and best practices.

Feel free to open an issue or pull request if you have any questions or need help.
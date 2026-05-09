# Solar Forecasting Module

This is a Python script designed to fetch solar power forecasts from OpenMeteo and update MongoDB for real-time data synchronization.

## Prerequisites

- Install the required libraries: `pika`, `psycopg2`, `pvlib`, `requests`, `json`, `logging`, `datetime`, `time`, `tzlocal` (for timezone conversion).
- Set up a PostgreSQL database with the specified credentials.
- Ensure MongoDB is running and accessible.

## Installation

```sh
pip install pika psycopg2 pvlib requests json datetime tzlocal
```

## Usage

1. **Fetch Weather Data:**
   ```python
   import os
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

2. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

3. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

4. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

5. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

6. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

7. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

8. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

9. **Fetch Weather Data:**
   ```python
   from dotenv import load_dotenv
   from pymongo import MongoClient

   load_dotenv()

   POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
   POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
   POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
   POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
   POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

   MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
   MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
   MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
   MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
   MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

   RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
   RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
   RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
   RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

   logging.basicConfig(
       level=logging.INFO,
       format="%(asctime)s [%(levelname)s] %(message)s",
       datefmt="%Y-%m-%d %H:%M:%S",
   )

   logger = logging.getLogger("solar-forecast")
   ```

10. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

11. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

12. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

13. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

14. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

15. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

16. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

17. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

18. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

19. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

20. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

21. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

22. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

23. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

24. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

25. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

26. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

27. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

28. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

29. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

30. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

31. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

32. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

33. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

34. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

35. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

36. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

37. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

38. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

39. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

40. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

41. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

42. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

43. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

44. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

45. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

46. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

47. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

48. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

49. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

50. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

51. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

52. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

53. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

54. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

55. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

56. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

57. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

58. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

59. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

60. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

61. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

62. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

63. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

64. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

65. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

66. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

67. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

68. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

69. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

70. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

71. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

72. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

73. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

74. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

75. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

76. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

77. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

78. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

79. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

80. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

81. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

82. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

83. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

84. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

85. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

86. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

87. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

88. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

89. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

90. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

91. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

92. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

93. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

94. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

95. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

96. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

97. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

98. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

99. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

100. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

101. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

102. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

103. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

104. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

105. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

106. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

107. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

108. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

109. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

10. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

11. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

12. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

13. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

14. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

15. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

16. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

17. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

18. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

19. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

20. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

21. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

22. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

23. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

24. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST = os.getenv("POSTGRES_HOST", "localhost")
    POSTGRES_PORT = int(os.getenv("POSTGRES_PORT", 5432))
    POSTGRES_USERNAME = os.getenv("POSTGRES_USERNAME", "admin")
    POSTGRES_PASSWORD = os.getenv("POSTGRES_PASSWORD", "admin")
    POSTGRES_NAME = os.getenv("POSTGRES_NAME", "default_db")

    MONGODB_HOST = os.getenv("MONGODB_HOST", "localhost")
    MONGODB_PORT = int(os.getenv("MONGODB_PORT", 27017))
    MONGODB_USERNAME = os.getenv("MONGODB_USERNAME", "admin")
    MONGODB_PASSWORD = os.getenv("MONGODB_PASSWORD", "admin")
    MONGODB_DB = os.getenv("MONGODB_DB", "default_db")

    RABBITMQ_HOST = os.getenv("RABBITMQ_HOST", "localhost")
    RABBITMQ_PORT = int(os.getenv("RABBITMQ_PORT", 5672))
    RABBITMQ_USERNAME = os.getenv("RABBITMQ_USERNAME", "admin")
    RABBITMQ_PASSWORD = os.getenv("RABBITMQ_PASSWORD", "admin")

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logger = logging.getLogger("solar-forecast")
    ```

25. **Fetch Weather Data:**
    ```python
    from dotenv import load_dotenv
    from pymongo import MongoClient

    load_dotenv()

    POSTGRES_HOST =
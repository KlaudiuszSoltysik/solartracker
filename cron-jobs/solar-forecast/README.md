# Solar Forecasting Module

This script is designed to generate solar power forecasts based on historical weather data and PV asset information.

## Prerequisites

- Python 3.x installed
- psycopg2 library for PostgreSQL database operations
- pvlib library for PV system calculations
- MongoDB for storing forecasted data

## Installation

1. Clone the repository: `git clone https://github.com/yourusername/solar-forecast.git`
2. Install dependencies: `pip install -r requirements.txt`

## Usage

1. Run the script: `python main.py`
2. The script will fetch weather data and PV asset information, then generate solar power forecasts for each farm.

## Technical Architecture

The module is built using a combination of Python, PostgreSQL, and MongoDB. It uses the following components:

- **PostgreSQL**: For storing forecasted data
- **MongoDB**: For storing assets' PV system information
- **PVlib**: For calculating PV system parameters based on weather data
- **Python**: For handling user input, processing data, and executing SQL queries

## Purpose

The module is designed to provide a reliable way for developers to generate solar power forecasts. It allows users to easily integrate with their existing systems by fetching historical weather data and PV asset information.

## Installation

1. Clone the repository: `git clone https://github.com/yourusername/solar-forecast.git`
2. Install dependencies: `pip install -r requirements.txt`

3. Run the script: `python main.py`

## Example Usage

```bash
$ python main.py
Starting solar power forecasting job started for 10 assets.
Processing farm: [farm_name_1]
Fetching weather data...
Processing farm: [farm_name_2]
Fetching weather data...
Processing farm: [farm_name_3]
Fetching weather data...
Processing farm: [farm_name_4]
Fetching weather data...
Processing farm: [farm_name_5]
Fetching weather data...
Processing farm: [farm_name_6]
Fetching weather data...
Processing farm: [farm_name_7]
Fetching weather data...
Processing farm: [farm_name_8]
Fetching weather data...
Processing farm: [farm_name_9]
Fetching weather data...
Processing farm: [farm_name_10]
Fetching weather data...
Forecasting job finished.
```

## Contributing

Contributions are welcome! If you have any questions or suggestions, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. You can find the license details in the `LICENSE` file.
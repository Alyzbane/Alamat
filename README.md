# Alamat Inventory System

A lightweight C++ inventory management system designed for small-scale inventory tracking.

## Features

**Core Functionality**:
- User authentication and access control
- Inventory item tracking and management
- Archive system for historical records
- Command-line interface with intuitive menu navigation

**Technical Highlights**:
- Built with modern C++ practices
- File-based storage system
- Password masking for secure input
- Cross-platform compatibility (Windows/Cygwin)

## Building from Source

**Prerequisites**:
- C++ compiler (GCC/MinGW or MSVC)
- Make or CMake build system

**Compilation**:
```bash
# Using Make
make

# Using CMake
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

After compilation, run the executable:
```bash
./alamat
```

The system will prompt for login credentials. Default admin credentials are provided in the documentation.

**Limitations**:
- Upon exiting the program, the data that was previously inserted will not be retrievable

**Recommmendations**
- Use external database like sqlite to store data

## Project Structure

```
Alamat/
├── src/
│   ├── alamat.cpp      # Main entry point
│   ├── archive.cpp     # Archive management
│   ├── login.cpp       # Authentication system
│   ├── menu.cpp        # Menu interface
│   └── screen.cpp      # Display handling
├── include/
│   └── *.h            # Header files
└── data/
    └── *.dat          # Data storage files
```

## Contributing

Feel free to submit issues and enhancement requests. Follow these steps to contribute:
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request
# Alamat

<p align="center">
  <img src="https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/98a0bcfc-ba20-41d8-8212-e0b9a0957496/diw7mag-0eca3aec-ebeb-4e6b-8dda-7429e13dbade.png/v1/fit/w_600,h_412,q_70,strp/project_alamat_by_xxxc2ginxxx_diw7mag-375w-2x.jpg?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7ImhlaWdodCI6Ijw9NDEyIiwicGF0aCI6IlwvZlwvOThhMGJjZmMtYmEyMC00MWQ4LTgyMTItZTBiOWEwOTU3NDk2XC9kaXc3bWFnLTBlY2EzYWVjLWViZWItNGU2Yi04ZGRhLTc0MjllMTNkYmFkZS5wbmciLCJ3aWR0aCI6Ijw9NjAwIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmltYWdlLm9wZXJhdGlvbnMiXX0.Df2jkGypjE8vP8ZVvfMCg6x6mv-Ef432a-CbYJN7c8Q" 
      loading="eager"
      alt="Sublime's custom image"
      style="display: block; margin: 0 auto"/>
</p>

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

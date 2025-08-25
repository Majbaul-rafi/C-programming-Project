# C-programming-Project

 C programs I solved during my university lab project.

# Customer Bookings for a Mobile Car Wash

## Project Overview
The **Car Wash Management System** is a console-based C application that automates customer bookings for a car wash service center. It allows the admin to manage bookings, generate bills, estimate costs, and maintain a persistent record of customer data using file handling.  

**Key Goals:**  
- Reduce human error in manual booking processes  
- Simplify cost calculation  
- Provide a structured workflow for managing multiple customers efficiently  
---

## Methodology

### System Design
- Built around a `Customer` structure storing:  
  - Booking ID  
  - Name  
  - Phone number  
  - Car model  
  - Service type (Basic / Premium / Deluxe + extra repairs)  
  - Total cost  

- Customer data is stored in an array of structures.  
- File handling is used to save/load data from `carwash.txt`.  

### Functional Components
1. **Admin Authentication**  
   - Login required (username: admin, password: 1234)  
   - Incorrect credentials exit the program  

2. **Data Initialization & Persistence**  
   - `loadData()` loads existing bookings  
   - `saveData()` writes bookings back to file  

3. **Add Booking**  
   - Enter customer details and select extra services  
   - Final cost = base cost + selected extras  
   - Duplicate Booking IDs prevented  

4. **View Bookings**  
   - Displays all customer records with details  

5. **Search Bookings**  
   - By ID (exact match)  
   - By Name or Phone (partial, case-insensitive)  

6. **Edit Booking**  
   - Update customer details and recalculate cost  

7. **Delete Booking**  
   - Permanently remove booking by ID  

8. **Show Price List / Cost Estimator**  
   - Display available services and extra repair costs  
   - Estimate total cost based on selected services  

9. **User Interface**  
   - Structured menu-driven interface with switch-case navigation  

---

## Uses
- Automates customer booking process  
- Reduces human error in cost calculation  
- Provides quick access to stored customer records  
- Allows efficient search and editing of records  
- Saves booking information permanently in `carwash.txt`  

---

## Limitations
- Static storage (max 100 bookings)  
- Basic authentication (hardcoded username & password)  
- File handling without encryption  
- Console-based interface (no GUI)  
- No multi-user support (single admin account)  

---

## Conclusion
The Car Wash Management System demonstrates important C programming concepts:  
- Structures and arrays for storing customer records  
- String handling for inputs  
- File handling for data storage and retrieval  
- Conditional logic & switch-case menus for interaction  

**Future Improvements:**  
- Database integration  
- Multi-user support  
- Enhanced authentication (password encryption)  
- Graphical User Interface (GUI)  

---



##  About Me

* Name:** Majbaul Islam Rafi  
* Student:** CSE, North South University  
* Email:** majbaul.rafi@gmail.com 
* GitHub:** https://github.com/Majbaul-rafi

---



Thanks for visiting! Feel free to clone, fork, or star the repo. 


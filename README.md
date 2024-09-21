# inventorymanagement
This C-based Inventory Management System enables administrators to manage products and users to view and purchase them. Product data is stored in Record.txt, with a menu-driven interface and file handling for efficient operations.
This program is an Inventory Management System written in C that allows an administrator to manage product records and a user to view and purchase products. The system operates by reading and writing product data from a file called Record.txt. The data includes product code, name, rate, quantity, weight (classification), and description. Here's a breakdown of the main functionalities:

Struct Definition:
ITEM Struct:
    Contains the details of a product (product_code, product_name, rate, quantity, weight, and description).
     A global instance of ITEM named item is used throughout the program to store data for operations like adding, updating, and deleting products.
Key Functions:
      isCodeAvailable & isCodeAvailableclass:

          These functions check if a product or classification is available in the Record.txt file by comparing the product code or weight with the records stored.
Admin Panel:

 addProduct: Allows the admin to add a new product if its code is not already present.
 display: Displays all products in a tabular format.
 search: Allows the admin to search by product code or classification.
 deleteRecord: Removes a product from the inventory.
 updateProduct: Updates an existing product’s details.
 saleProduct: Allows the admin to record the sale of a product, reducing its quantity.
 closeApp: Exits the program after confirmation.
 
User Panel:

 display: Displays available products.
 search: Allows users to search products by code or classification.
 saleProduct: Allows users to "buy" a product by entering its code and quantity, reducing stock accordingly.
 get_int:

          A utility function that ensures valid integer input from the user.
mainMenu:

  Presents the main options to the user, allowing access to either the Admin or User panels or exit the program.
  Description of Features:
  File Handling: The program uses file I/O to store and retrieve product details from Record.txt. Products are added, updated, and deleted by reading from and writing to the file.
  Input Validation: The program includes robust input validation, ensuring that numeric inputs are positive integers, and product codes are checked for availability before being added.
  Interactive Menu: Users and admins are guided through options via a menu-driven interface, with choices for adding, viewing, updating, deleting, and searching products.
  
This system allows efficient management of products in an inventory, enabling both user and admin operations.

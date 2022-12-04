# mataas-na-grade-sure-na-to-99.9-

<h2> Building from the source </h2>
<p> Compile it using these make rules. Use the command prompt for windows or bash for linux or whatever you have </p>
<code> make entry.o login.o screen.o user.o alamat </code>

<h2> How to Run </h2>
<p>Type this in the command prompt</p>

<h3>Windows</h3>
<code> alamat </code>
<h3>Linux</h3>
<code> .\alamat </code>


<h2> Help </h2>
<p>If it returned some error during compilation. Remove the "-static-libstdc++" rule in the makefile...</p>

Kulang pa dito ay: <br />
 <s>1. User/Admin interface</s>  
 <s> 1.1. back to first panel</s>
  
 2. search(func)
   2.1. archive books are sorted sa kanilang catalog
    <s>- author
       - price
       - isbn
       - title </s>  
       - price (min, high) <br />
       
 3. user()
  <s>    3.1 show recent bought book
    3.2 show history of transactions </s>  
    
 4. buying()<br/>
    4.1 Discount / Promo / Voucher 
    <s> 4.2 using the Func::seach() to sort the query </s>  
   <b> Transactions History will not be sorted</b>
    
 5. resibo()
    > redirect the information of picked book into a file
 <s>    > formatted using the buying()  </s>  
 
<br />Aayusin lang muna sa version na ito ay:  <br />
 1. <s> mga class objects, yung sa main features eg. insert, search...
    1.1 hihiwalay/organize nalang yung mga helper functions </s>  
 2. <s> exception handling 
    i.e. mga int at double error inputs pag may bagong enter na data </s>  
 3. <s> struct or vector class sa paghahandle ng mga catalog </s> napili ay pointer to dynamically allocated arrays
 4. Adding discount to the books </br>
 <strong>5. %1. messy code functions, lipat sa class or something</strong>

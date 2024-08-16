#This is a password encrypter/decryptor made using python
action = input("What would you like to do? \nEncrypt\nDecrypt\n")
if action == "Encrypt":
    message = input("Enter the message to encrypt: ")
    translated = ''
    i = len(message) - 1
    while i >= 0:
        translated = translated + message[i]
        i = i - 1
    msg = "Your encrypted message is: "
    print(msg + translated)
elif action == "Decrypt":
   
    message = input("Enter the message to decrypt: ")
    translated = ''
    i = len(message) - 1
    while i >= 0:
        translated = translated + message[i]
        i = i - 1
    msg = "Your decrypted message is: "
    print(msg + translated)
else:
    print("Invalid option selected.")

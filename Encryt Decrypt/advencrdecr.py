shift = 3

action = input("What would you like to do? \nEncrypt\nDecrypt\n")
if action == "Encrypt":
    message = input("Enter the message to encrypt: ")
    translated = ''
    for char in message:
        translated += chr(ord(char) + shift)
    msg = "Your encrypted message is: "
    print(msg + translated)
elif action == "Decrypt":
    message = input("Enter the message to decrypt: ")
    translated = ''
    for char in message:
        translated += chr(ord(char) - shift)
    msg = "Your decrypted message is: "
    print(msg + translated)
else:
    print("Invalid option selected.")

# Datos
codigo = 202225328
nombres = "Erik\tAlejandro\r\n"
apellidos = "Garcia\tDuarte\r\n"
cedula = "1016592716\r\n\0"
edad = 19
cienANacimiento = edad - 100

# Escribir datos en un archivo binario
with open("datos.bin", "wb") as f:
    f.write(codigo.to_bytes(4, 'big'))  # Código como un entero de 4 bytes en formato big-endian
    f.write(nombres.encode('utf-8'))  # Nombres codificados en UTF-8
    name_length = len(nombres.encode('utf-8'))
    # Si el nombre no ocupa 54 bytes, rellenar con 00 hasta completarlos
    if name_length < 50:
        f.write(b'\0' * (50 - name_length))

    f.write(apellidos.encode('utf-8'))  # Apellidos codificados en UTF-8
    apellidos_length = len(apellidos.encode('utf-8'))
    if apellidos_length < 43:
        f.write(b'\0' * (43 - apellidos_length))
    f.write(cedula.encode('ascii'))  # Cédula codificada en ASCII
    cedula_length = len(cedula.encode('ascii'))
    if cedula_length != 13:
        error = "La cédula debe tener 13 caracteres"
        raise ValueError(error)
    
    f.write(edad.to_bytes(1, 'big'))    # Edad como un entero de 1 byte en formato big-endian
    f.write(cienANacimiento.to_bytes(2, 'big', signed=True))  # Diferencia a 100 como un entero de 2 bytes en formato big-endian con signo    name_length = len(nombres.encode('utf-8'))
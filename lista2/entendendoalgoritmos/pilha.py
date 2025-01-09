#pilha de chamada

def sauda (nome):
    print("Olá, " + nome + "!")
    sauda2(nome)
    print("Preparando-se para dizer tchau...")
    tchau(nome)

def sauda2(nome):
    print("Como vai, " + nome + "?")

def tchau():
    print ("ok, tchau!")
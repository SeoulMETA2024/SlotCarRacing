import pyfiglet

def print_data(place, nickname,time) -> None:

    art = pyfiglet.figlet_format(f"{place} : {nickname}:{time}\n")
    print(art + '\n\n\n\n\n\n\n\n\n')
    return None
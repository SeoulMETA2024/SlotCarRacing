import pyfiglet

def print_data(place, nickname,time) -> None:

    art = pyfiglet.figlet_format(f"{place} : {nickname}:{time}\n")#줄띄우기가 먹는지 안먹는지 모름
    print(art + '\n\n\n\n\n\n\n\n\n')
    return None
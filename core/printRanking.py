import pyfiglet

def print_data(place, nickname,time) -> None:

    art = pyfiglet.figlet_format(f"{place} : {nickname}_{time[0]}:{time[1]}")
    print(art)
    
    return 



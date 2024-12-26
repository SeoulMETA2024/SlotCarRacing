import pyfiglet

def print_data(place, nickname,time) -> None:
    # text = f"*****\n{place} : {nickname}:{time}\n*****"

    text = f"""
    *****
    {place} : {nickname}:{time}
    *****
    """

    art = pyfiglet.figlet_format(text)#줄띄우기가 먹는지 안먹는지 모름
    print(art)
    return None

if __name__=="__main__":
    print_data("place", "@sng___yn", "00:00:00")
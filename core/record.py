class Record:
    def __init__(self):

        self.top = 0
        self.ranking = []
        self.isExceptional = lambda res: res<=self.ranking

        pass
    def newRecord(self,result) -> dict:   
        self.ranking.append({'name':result[0],'result':result[1]})
    
    def sortRanking(self) -> dict:
        self.ranking = sorted(self.ranking, key=lambda x: self.secToMs(x['result']))
        return
    

    def secToMs(self,value:tuple) -> int:
        value = value[0] + value[1]*60
        return value


import os 
import shutil


file_path = os.path.dirname(os.path.realpath(__file__)) 
file_path.replace('\\', '\\\\')

article_aclass = ['pol', 'eco', 'nav', 'lif', 'wor', 'sci']

pol_TFIDF = { }
eco_TFIDF = { }
nav_TFIDF = { }
lif_TFIDF = { }
wor_TFIDF = { }
sci_TFIDF = { }


#TF-IDF 수치 받아오기

for i in article_aclass:
    with open(f"{file_path}\\TF-IDF 수치\\{i}.txt", "r", encoding="utf8") as file:
        temp = file.read()
        temp = temp.replace('{', '')
        temp = temp = temp.replace('}', '')
        temp = temp.replace("'", '')
        temp = temp.replace(' ', '')
        temp = temp.split(',')
        for j in temp:
            a = j.split(':')
            if i == 'pol':
                pol_TFIDF[a[0]] = float(a[1])
            elif i == 'eco':
                eco_TFIDF[a[0]] = float(a[1])
            elif i == 'nav':
                nav_TFIDF[a[0]] = float(a[1])
            elif i == 'lif':
                lif_TFIDF[a[0]] = float(a[1])
            elif i == 'wor':
                wor_TFIDF[a[0]] = float(a[1])
            elif i == 'sci':
                sci_TFIDF[a[0]] = float(a[1])


#저장할 폴더 생성
if os.path.exists(file_path + '\\뉴스 분류 로그'):
    shutil.rmtree(file_path + '\\뉴스 분류 로그') 
os.mkdir(file_path + '\\뉴스 분류 로그') 

#자연어처리한 파일을 정리할 폴더를 종류별로 생성
for i in article_aclass:
    os.mkdir(file_path + '\\뉴스 분류 로그\\' + i)
    



yes = 0
no = 0

for i in article_aclass:
    for j in range(1, len(os.listdir(file_path + '\\자연어 처리 로그\\' + i)) + 1):
        article_TFIDF_score = {'pol':0, 'eco':0, 'nav':0, 'lif':0, 'wor':0, 'sci':0}
        with open(f"{file_path}\\자연어 처리 로그\\{str(i)}\\자연어 처리 로그 {j}번째.txt", "r", encoding="utf8") as file:
            log_read = file.read().split(' ')
        for t in log_read:
            if t in pol_TFIDF.keys():
                article_TFIDF_score['pol'] += pol_TFIDF[t]
            if t in eco_TFIDF.keys():
                article_TFIDF_score['eco'] += eco_TFIDF[t]
            if t in nav_TFIDF.keys():
                article_TFIDF_score['nav'] += nav_TFIDF[t]
            if t in lif_TFIDF.keys():
                article_TFIDF_score['lif'] += lif_TFIDF[t]
            if t in wor_TFIDF.keys():
                article_TFIDF_score['wor'] += wor_TFIDF[t]
            if t in sci_TFIDF.keys():
                article_TFIDF_score['sci'] += sci_TFIDF[t]



        field = 'pol'
        field_score = 0
        for m in article_aclass:
            if article_TFIDF_score[m] > field_score:
                field = m
                field_score = article_TFIDF_score[m]
        with open(f"{file_path}\\뉴스 크롤링 로그\\{i}\\크롤링 로그 {j}번째.txt",
         "r", encoding="utf8") as file:
            tmep = file.read()
        num = len(os.listdir(file_path + '\\뉴스 분류 로그\\' + field)) + 1
        with open(f"{file_path}\\뉴스 분류 로그\\{field}\\뉴스 분류 로그 {num}번째.txt", "w", encoding="utf8") as file:
            file.write(tmep)
        if field == i:
            yes += 1
        else:
            no += 1

print(f"총:{yes+no} yes:{yes} no:{no}")

                



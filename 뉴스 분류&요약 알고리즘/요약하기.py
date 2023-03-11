#TF-IDF점수가 가장 높은 문장을 찾기

# 파일 관리를 위한 모듈 추가
import os #Operating System의 약자, 운영체제에서 제공되는 여러 기능을 수행할 수 있게 해줌
import shutil


file_path = os.path.dirname(os.path.realpath(__file__))  # 폴더 절대경로
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



if os.path.exists(file_path + '\\뉴스 요약 로그'): 
    shutil.rmtree(file_path + '\\뉴스 요약 로그') 
os.mkdir(file_path + '\\뉴스 요약 로그') 


for i in article_aclass:
    os.mkdir(file_path + '\\뉴스 요약 로그\\' + 'i')



for i in article_aclass:
    for j in range(1, len(os.listdir(file_path + '\\뉴스 분류 로그\\' + i)) + 1):
        with open(f"{file_path}\\뉴스 분류 로그\\{i}\\뉴스 분류 로그 {j}번째.txt",
         "r", encoding="utf8") as file:
            read_sentence = str(file.read())
        sentence_TFIDF_score = {}
        sentence = read_sentence.split('.')
        for z in range(0, len(sentence)):
            sentence_TFIDF_score[z] = 0
        for z in range(0, len(sentence)):
            if i == 'pol':
                for m in pol_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += pol_TFIDF[m]
            if i == 'eco':
                for m in eco_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += eco_TFIDF[m]
            if i == 'nav':
                for m in nav_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += nav_TFIDF[m]
            if i == 'lif':
                for m in lif_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += lif_TFIDF[m]
            if i == 'wor':
                for m in wor_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += wor_TFIDF[m]
            if i == 'sci':
                for m in sci_TFIDF.keys():
                    if m in sentence[z]:
                        sentence_TFIDF_score[z] += sci_TFIDF[m]

        most_important_sentence = 'none'
        most_important_sentence_score = 0
        for n in sentence_TFIDF_score:
            if sentence_TFIDF_score[n] > most_important_sentence_score:
                most_important_sentence = n
                most_important_sentence_score = sentence_TFIDF_score[n]
        with open(f"{file_path}\\뉴스 요약 로그\\{i}\\뉴스 요약 로그 {j}번째.txt",
         "w", encoding="utf8") as file:
            file.write(sentence[most_important_sentence])





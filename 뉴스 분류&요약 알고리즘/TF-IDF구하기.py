


# 파일 관리를 위한 모듈 추가
import os #Operating System의 약자, 운영체제에서 제공되는 여러 기능을 수행할 수 있게 해줌
import shutil

import math #로그 사용하기 위해

file_path = os.path.dirname(os.path.realpath(__file__))  # 폴더 절대경로
file_path.replace('\\', '\\\\')

article_aclass = ['pol', 'eco', 'nav', 'lif', 'wor', 'sci']

#각 종류의 기사에 단어가 얼마나 들어가 있는지 카운트하는 딕셔너리 변수
pol_TF = { }
eco_TF = { }
nav_TF = { }
lif_TF = { }
wor_TF = { }
sci_TF = { }

#단어 갯수 새는 함수

def function_TF(field, word_list):
    word_list = str(word_list).split(' ')
    for i in word_list:
        if field == 'pol':
            if i.find(' ') == -1:
                if i in pol_TF:
                    pol_TF[i] += 1
                else:
                    pol_TF[i] = 1
        if field == 'eco':
            if i.find(' ') == -1:
                if i in eco_TF:
                    eco_TF[i] += 1
                else:
                    eco_TF[i] = 1

        if field == 'nav':
            if i.find(' ') == -1:
                if i in nav_TF:
                    nav_TF[i] += 1
                else:
                    nav_TF[i] = 1
        if field == 'lif':
            if i.find(' ') == -1:
                if i in lif_TF:
                    lif_TF[i] += 1
                else:
                    lif_TF[i] = 1
                    
        if field == 'wor':
            if i.find(' ') == -1:
                if i in wor_TF:
                    wor_TF[i] += 1
                else:
                    wor_TF[i] = 1
        if field == 'sci':
            if i.find(' ') == -1:
                if i in sci_TF:
                    sci_TF[i] += 1
                else:
                    sci_TF[i] = 1
               




# with open(f"{file_path}\\pol\\크롤링 로그 1번째.txt", "r", encoding="utf8") as file:
#     temp = clean_korean_documents(str(file.read()))
# function_TF('pol', temp)
# print(pol_TF)



#TF구하기
for i in article_aclass:
    for j in range(1, len(os.listdir(file_path + '\\자연어 처리 로그\\' + i)) + 1):
        with open(f"{file_path}\\자연어 처리 로그\\{str(i)}\\자연어 처리 로그 {j}번째.txt", "r", encoding="utf8") as file:
            function_TF(i, file.read())






print('TF 구하기 완료')

#TF-IDF구해서 새로운 기사를 봤을 대 pol의 키워드와 겹치는 것들 있는지 검사, 있으면 그 단어의 pol의 TF-IDF에 따라 점수 줌, 다른 분야도 똑같이 다 검사한 후 가장 높은 분야가 기사의 분야인것으로 취급
#TF-IDF 구하기
#여기선 문서집합(ex 정치계열 문서 집합)을 하나의 문서로 봄
#TF(단어 빈도): 로그 스케일 빈도: tf(t,d) = log (f(t,d) + 1); 문서 d 내에서 단어 t의 총 빈도를 f(t,d)
#IDF(역문서 빈도): 전체 문서의 수를 해당 단어를 포함한 문서의 수로 나눈 뒤 로그 6/

#IDF 구하기

pol_IDF = { }
eco_IDF = { }
nav_IDF = { }
lif_IDF = { }
wor_IDF = { }
sci_IDF = { }

for i in pol_TF.keys():
    include_document = 1
    if i in eco_TF.keys():
        include_document += 1
    if i in nav_TF.keys():
        include_document += 1
    if i in lif_TF.keys():
        include_document += 1
    if i in wor_TF.keys():
        include_document += 1
    if i in sci_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    pol_IDF[i] = IDF

for i in eco_TF.keys():
    include_document = 1
    if i in pol_TF.keys():
        include_document += 1
    if i in nav_TF.keys():
        include_document += 1
    if i in lif_TF.keys():
        include_document += 1
    if i in wor_TF.keys():
        include_document += 1
    if i in sci_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    eco_IDF[i] = IDF

for i in nav_TF.keys():
    include_document = 1
    if i in eco_TF.keys():
        include_document += 1
    if i in pol_TF.keys():
        include_document += 1
    if i in lif_TF.keys():
        include_document += 1
    if i in wor_TF.keys():
        include_document += 1
    if i in sci_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    nav_IDF[i] = IDF

for i in lif_TF.keys():
    include_document = 1
    if i in eco_TF.keys():
        include_document += 1
    if i in nav_TF.keys():
        include_document += 1
    if i in pol_TF.keys():
        include_document += 1
    if i in wor_TF.keys():
        include_document += 1
    if i in sci_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    lif_IDF[i] = IDF


for i in wor_TF.keys():
    include_document = 1
    if i in eco_TF.keys():
        include_document += 1
    if i in nav_TF.keys():
        include_document += 1
    if i in lif_TF.keys():
        include_document += 1
    if i in pol_TF.keys():
        include_document += 1
    if i in sci_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    wor_IDF[i] = IDF


for i in sci_TF.keys():
    include_document = 1
    if i in eco_TF.keys():
        include_document += 1
    if i in nav_TF.keys():
        include_document += 1
    if i in lif_TF.keys():
        include_document += 1
    if i in wor_TF.keys():
        include_document += 1
    if i in pol_TF.keys():
        include_document += 1
    IDF = math.log(6/include_document)
    sci_IDF[i] = IDF

# print(pol_IDF)
# print(eco_IDF)
# print(nav_IDF)
# print(lif_IDF)
# print(wor_IDF)
# print(sci_IDF)

print('IDF 구하기 완료')


#TF-IDF 구하기
#['pol', 'eco', 'nav', 'lif', 'wor', 'sci']


pol_TFIDF = { }
eco_TFIDF = { }
nav_TFIDF = { }
lif_TFIDF = { }
wor_TFIDF = { }
sci_TFIDF = { }

for i in pol_TF.keys():
    pol_TFIDF[i] = pol_TF[i] * pol_IDF[i]
for i in eco_TF.keys():
    eco_TFIDF[i] = eco_TF[i] * eco_IDF[i]
for i in nav_TF.keys():
    nav_TFIDF[i] = nav_TF[i] * nav_IDF[i]
for i in lif_TF.keys():
    lif_TFIDF[i] = lif_TF[i] * lif_IDF[i]
for i in wor_TF.keys():
    wor_TFIDF[i] = wor_TF[i] * wor_IDF[i]
for i in sci_TF.keys():
    sci_TFIDF[i] = sci_TF[i] * sci_IDF[i]




if os.path.exists(file_path + '\\TF-IDF 수치'):
    shutil.rmtree(file_path + '\\TF-IDF 수치') 
os.mkdir(file_path + '\\TF-IDF 수치') 


with open(f"{file_path}\\TF-IDF 수치\\pol.txt", "w", encoding="utf8") as file:
    file.write(str(pol_TFIDF))
with open(f"{file_path}\\TF-IDF 수치\\eco.txt", "w", encoding="utf8") as file:
    file.write(str(eco_TFIDF))
with open(f"{file_path}\\TF-IDF 수치\\nav.txt", "w", encoding="utf8") as file:
    file.write(str(nav_TFIDF))
with open(f"{file_path}\\TF-IDF 수치\\lif.txt", "w", encoding="utf8") as file:
    file.write(str(lif_TFIDF))
with open(f"{file_path}\\TF-IDF 수치\\wor.txt", "w", encoding="utf8") as file:
    file.write(str(wor_TFIDF))
with open(f"{file_path}\\TF-IDF 수치\\sci.txt", "w", encoding="utf8") as file:
    file.write(str(sci_TFIDF))

print("TF-IDF 구하기 완료")

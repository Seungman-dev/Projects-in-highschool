
# 크롤링을 위한 모듈 추가
from bs4 import BeautifulSoup as bs # bs4라는 모듈에서 BeautifulSoup라는 클래스를 bs라는 이름으로 불러옴
import requests

# 파일 관리를 위한 모듈 추가
import os #Operating System의 약자, 운영체제에서 제공되는 여러 기능을 수행할 수 있게 해줌
import shutil #파일 관리

file_path = os.path.dirname(os.path.realpath(__file__)) + '\뉴스 크롤링 로그' # 뉴스 크롤링 로그 저장하는 폴더의 절대경로
file_path.replace('\\', '\\\\')

#크롤링할 웹페이지 주소
site_url = "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=10"
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=100" - 네이버 뉴스 정치
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=101" - 네이버 뉴스 경제
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=102" - 네이버 뉴스 사회
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=103" - 네이버 뉴스 생활/문화
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=104" - 네이버 뉴스 세계
# "https://news.naver.com/main/main.naver?mode=LSD&mid=shm&sid1=105" - 네이버 뉴스 IT/과학

article_aclass = ['pol', 'eco', 'nav', 'lif', 'wor', 'sci']

article_aclass_count = {'pol':0, 'eco':0, 'nav':0, 'lif':0, 'wor':0, 'sci':0} #어느 분야에서 가져온 기사인지 구별하기 위한 딕셔너리

news_find = []

for i in range(0, 6):
    site_response = requests.get(site_url + str(i), headers={'User-Agent':'Mozilla/5.0'}) #크롤링, headers={'User-Agent':'Mozilla/5.0'} -> 안티크롤링
    site_html = site_response.text #응답 html코드를 text형식으로 변환
    site_bs_obj = bs(site_html) #site_bs_obj : 응답받은 html코드를 BeautifulSoup에 사용하기 위하여 인스턴스 지정(html 코드를 soup 객체(site_bs_obj)로 받아옴).
    #print(site_bs_obj)
    #print(site_bs_obj.find_all('a', {'class':f'cluster_text_headline nclicks(cls_{article_aclass[i]}.clsart)'}))
    news_find += site_bs_obj.find_all('a', {'class':f'cluster_text_headline nclicks(cls_{article_aclass[i]}.clsart)'}) #뉴스 제목과 링크가 포함된 리스트 
    #<a class="cluster_text_headline nclicks(cls_sci.clsart)" href="https://n.news.naver.com/mnews/article/079/0003661568?sid=105">필즈상 허준이 교수 "모든 연구, 추억 속 앨범처럼 소중해"</a> 를 한개의 요소로 하는 리스트 형식으로 나옴
    print(f"{article_aclass[i]}: {len(site_bs_obj.find_all('a', {'class':f'cluster_text_headline nclicks(cls_{article_aclass[i]}.clsart)'}))}개")

    article_aclass_count[article_aclass[i]] = len(news_find) #어느 분야에서 가져온 기사인지 구별하기 위함

print(f"총 갯수: {len(news_find)}개")



#print(news_find)

#저장할 폴더 생성
if os.path.exists(file_path) != True: # '뉴스 크롤링 로그'라는 이름의 폴더가 존재하지 않으면
    os.mkdir(file_path) # '뉴스 크롤링 로그'라는 이름의 폴더 생성

for i in article_aclass:
    
    if os.path.exists(file_path + '\\' + i) != True: # '뉴스 크롤링 로그'폴더 안에 각 분야의 이름을 가진 폴더가 존재하지 않으면 
        os.mkdir(file_path + '\\' + i) # 각 분야의 이름을 가진 폴더 생성



num = 1 #뉴스 갯수 카운트
temp_count = len(os.listdir(file_path + '\\pol')) +1 #뉴스 갯수 카운트
last_type = 'pol' #뉴스 카운트 타입

for i in news_find:
    #리스트에서 뉴스 제목과 링크 골라내기
    title = str(i).split('>')[1].replace('</a', '')
    link = (str(i).split('"'))[3]

    #골라낸 뉴스 링크 크롤링
    news_response = requests.get(link, headers={'User-Agent':'Mozilla/5.0'}) 
    news_html = news_response.text 
    news_bs_obj = bs(news_html)

    news_content_find = str(news_bs_obj.find_all('div', {'id':'dic_area'}))

    #뉴스 내용만 골라내기
    news_content_find = news_content_find.replace('[', '')
    news_content_find = news_content_find.replace(']', '')
    news_content_find = news_content_find.replace('amp;', '')
    news_content_find = news_content_find.replace('\n', '')
    news_content_find = news_content_find.replace('"', ' ')
    news_content_find = news_content_find.replace("'", ' ')
    news_content_find = news_content_find.replace('>', '<') #구문자 통합

    news_content_find = news_content_find.split('<')

    news_content_final = ""
    for i in news_content_find:
        if 'img' not in i and 'div' not in i and 'class' not in i and 'br' not in i and '--' not in i and 'span' not in i and 'em' not in i and 'strong' not in i and '사진' not in i and '제공' not in i and '출처' not in i:
            news_content_final = news_content_final + i


    
    
    
    #뉴스의 제목과 링크, 크롤링한 데이터를 txt 파일로 저장
    for i in article_aclass:
        if num <= article_aclass_count[i]:
            if last_type != i:
                temp_count = len(os.listdir(file_path + '\\' + i)) +1
            last_type = i
            with open(f"{file_path}\\{str(i)}\\크롤링 로그 {temp_count}번째.txt", "w", encoding="utf8") as file: #절대경로에 파일 만들기
                file.write(str(news_content_final))
                print(temp_count)
                break
    temp_count += 1
    

    num += 1 #뉴스 카운트 1 증가


print('크롤링 완료')


#encoding:utf-8
import os
import urllib2
import re
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

class baiduDownloader:
	searchUrl = 'http://music.baidu.com/search?key='
	downloadUrl = 'http://music.baidu.com'
	downloadSuf = '/download?__o=%2Fsearch'

	def __init__(self, name, quality='mid'):
		if (quality == 'mid'):
			self.m_quality = 64
		elif (quality == 'high'):
			self.m_quality = 192
		else:
			self.m_quality = 128

		self.m_name = name

	def work(self):
		self.m_page = self.getSearchPage(self.m_name)
		self.m_songInfo = self.listSongs(self.m_page)
		self.m_chosenSong = self.chooseSong()
		self.downloadSong()

	def getSearchPage(self, name):
		fullUrl = str(self.searchUrl) + str(name)
		reponse = urllib2.urlopen(fullUrl)
		pageData = reponse.read()
		return pageData

	# input: searchPage, output: songList
	def listSongs(self, pageData):
		songInfo = []
		print "songs list:\n",
		songPattern = r'''<a href="(/song/[0-9]+).*" class="(.*)" data-songdata='(.*)' title="([^"]*)"([\s\S]*?)<span class="author_list" title="([^"]*)">'''
		subStr = re.findall(songPattern, pageData)

		for index in range(0, len(subStr)):
			title = subStr[index][3]
			author = subStr[index][5]
			downloadUrl = self.downloadUrl + str(subStr[index][0]) + self.downloadSuf
			songInfo.append([title, author, downloadUrl])
		return songInfo

	def chooseSong(self):
		for index, aSongInfo in enumerate(self.m_songInfo):
			print ("%d. song:%s author:%s\n" %(index + 1, aSongInfo[0], aSongInfo[1])),
		song_index = raw_input("choose song:")
		if (int(song_index) < 1 or int(song_index) > len(self.m_songInfo)):
			print ("wrong song index\n")
			exit(1)
		else:
			return int(song_index) - 1


	def downloadSong(self):
		downloadUrl = self.m_songInfo[int(self.m_chosenSong)][2]
		downloadPage = urllib2.urlopen(downloadUrl)
		downloadPageData = downloadPage.read()
		downloadPattern = r'''<a data-btndata='[^']*'  href="/data/music/file\?link=([^"]*)"  id="([0-9]+)"  class="[^"]*" >'''
		downloadLink = re.findall(downloadPattern, downloadPageData)
		singerStr = self.m_songInfo[int(self.m_chosenSong)][1]
		songStr = str(self.m_songInfo[int(self.m_chosenSong)][0]) + str(self.m_songInfo[int(self.m_chosenSong)][1])
		filePath = './songs/' +  singerStr + '/' + songStr + ".mp3"
		if (os.path.exists(filePath)):
			print "Skip, %s has alread exit\n" %(str(filePath))
			return

		downloaded = False
		# download "高品质"
		for index, link in enumerate(downloadLink):
			realLink = downloadLink[index][0]
			quality = downloadLink[index][1]
			try: downloader = urllib2.urlopen(realLink)
			except :
				continue
			print "Downloading\n"
			if (not os.path.exists('./songs/' + singerStr)):
				os.mkdir('./songs/'+ singerStr)
			output = open(filePath, 'wa')
			while True:
				buffer = downloader.read(1024 * 256)
				if not buffer:
					break
				output.write(buffer)
			downloaded = True
			break

		if (downloaded):
			return
		# down other link
		panPattern = r'''来源链接：([\s\S]*?)<a([\s\S]*?)href="([^"]*)">'''
		m = re.search(panPattern, downloadPageData)
		
		if (m):
			panPage = urllib2.urlopen(m.group(3).replace('&amp;', '&'))
		panPageData = panPage.read()

		#print panPageData
		downloadPattern = r'''<a class="new-dbtn"([\s\S]*?)href="([^"]*)"'''
		m = re.search(downloadPattern, panPageData)
		
		if (m):
			realLink = m.group(2)
		realLink.replace('&amp;', '&')
		try: downloader = urllib2.urlopen(realLink.replace('&amp;', '&'))
		except :
			return
		print "Downloading\n"
		if (not os.path.exists('./' + singerStr)):
			os.mkdir('./'+ singerStr)
		output = open(filePath, 'wa')
		while True:
			buffer = downloader.read(1024 * 256)
			if not buffer:
				break
			output.write(buffer)
		downloaded = True

if __name__ == '__main__':
	songName = raw_input('search song >')
	downloader = baiduDownloader(songName)
	downloader.work()


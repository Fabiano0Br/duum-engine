#!/bin/bash
mkdir -p ata MOVIE
cd ata/
youtube-dl 'https://www.youtube.com/watch?v=zJtGnnhYZOo'
ffmpeg -i android52\ -\ dancing\ all\ night-zJtGnnhYZOo.mkv -filter:v tblend -r 29.970 -vf scale=1280:720 result.mp4
ffmpeg -i android52\ -\ dancing\ all\ night-zJtGnnhYZOo.mkv ../audio.wav
ffmpeg -i result.mp4 -vsync 0 -q:v 8 scene%5d.jpg
rm ../MOVIE/*
mv *.jpg ../MOVIE/
cd ../

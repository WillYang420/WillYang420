start-transcript build.log
cd \Users\jgriffith\git\2616j\tp2616j-red
prosv5 make clean
prosv5 make
prosv5 upload --slot 1 --name Red-Front  --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-Blue
prosv5 make clean
prosv5 make
prosv5 upload --slot 2 --name Blue-Front  --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-RedBack
prosv5 make clean
prosv5 make
prosv5 upload --slot 3 --name Red-Back  --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-BlueBack
prosv5 make clean
prosv5 make
prosv5 upload --slot 4 --name Blue-Back  --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-RedSkills
prosv5 make clean
prosv5 make
prosv5 upload --slot 7 --name Skills  --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-RedFPlat
prosv5 make clean
prosv5 make
prosv5 upload --slot 5 --name RedFPlat --no-run-after
cd \Users\jgriffith\git\2616j\tp2616j-BluePlat
prosv5 make clean
prosv5 make
prosv5 upload --slot 6 --name BluePlat --no-run-after
stop-transcript
invoke-item \Users\jgriffith\git\2616j\build.log

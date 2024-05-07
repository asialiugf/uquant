import csv
import pandas as pd  # 用于数据输出
list = []
csv_reader = csv.reader(open("./指数板块.csv"))
for line in csv_reader:
    line1 = [line[0], line[1], line[2]]
    x = line[3]
    for i in range(len(line)-4):
        x = x+line[i+4]
    line1.append(x)
    line1.append("sh")
    print(line1)
    list.append(line1)
test = pd.DataFrame(data=list)  # 将数据放进表格
test.to_csv('test.csv', index=False)  # 数据存入csv,存储位置及文件名称

import os
import dolphindb.settings as keys
import dolphindb as db
s = db.session()
s.connect("localhost", 8848)
s.login("admin","123456")
s.database(dbPath="dfs://stock1f")
#trade = s.loadTable(tableName="stock1f",dbPath="dfs://stock1f")
#trade = s.loadTable(tableName="stock1f",dbPath="dfs://stock1f",sql="select count(*) from stock1f")
trade = s.loadTableBySQL(tableName="stock1f", dbPath="dfs://stock1f", sql="select * from stock1f where stockid='000007' and  date>2010.01.01")
print(trade.rows)
print(trade.schema)
print(trade.toDF())

script1='''
db=database("dfs://stock1f");
pt=loadTable(db,"stock1f");
select * from pt where stockid="000007";
'''
block= s.run(script1, fetchSize = 8192)
total = 0
while block.hasNext():
    print(block)
    tem = block.read()
    print(tem)
    total+=len(tem)

print("total=", total)

import dolphindb as ddb
s = ddb.session()
s.connect("localhost", 8848)
s.login("admin","123456")
#trade = s.loadTable(tableName="stock1f",dbPath="dfs://stock1f")
#trade = s.loadTable(tableName="stock1f",dbPath="dfs://stock1f",sql="select count(*) from stock1f")
trade = s.loadTableBySQL(tableName="stock1f", dbPath="dfs://stock1f", sql="select * from stock1f where date>2010.01.01")
print(trade.rows)
print(trade.schema)
print(trade.toDF())


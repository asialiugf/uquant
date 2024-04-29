import urllib3
import pandas as pd


def get_today_data():
    url = "http://api.jinshuyuan.net/get_stk_bar_today"
    http = urllib3.PoolManager()
    r = http.request("GET", url, preload_content=False)
    content = r.read()
    content = str(content, encoding="utf-8")
    content = [item.split(",") for item in content.split("<br/>")]
    col_name = [item.replace('"', "").replace("'", "") for item in content[0]]
    col_data = content[1:]
    df = pd.DataFrame(col_data, columns=col_name)
    df = df.dropna()
    print(df)


if __name__ == "__main__":
    get_today_data()

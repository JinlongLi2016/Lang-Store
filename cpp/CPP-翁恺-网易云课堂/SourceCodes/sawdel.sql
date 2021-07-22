WITH COL_CTE(Id,Name,ParentId,tLevel )
AS
(
    --基本语句
    SELECT Id,Name,ParentId,0 AS tLevel FROM Col
    WHERE ParentId = 0
    UNION ALL
    --递归语句
    SELECT c.Id,c.Name,c.ParentId,ce.tLevel+1 AS tLevel FROM COL as c
    INNER JOIN COL_CTE AS ce 　　--递归调用
    ON c.ParentId = ce.Id
)
SELECT * FROM COL_CTE

mi = mi.set_names("new name", level=0)
mi = mi.set_names("new name", level=0)
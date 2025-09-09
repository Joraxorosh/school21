CREATE TABLE routes (
    point1 VARCHAR,
    point2 VARCHAR,
    cost INT
);

INSERT INTO routes
VALUES
    ('a','b',10),
    ('b','a',10),
    ('a','c',15),
    ('c','a',15),
    ('a','d',20),
    ('d','a',20),
    ('b','d',25),
    ('d','b',25),
    ('c','d',30),
    ('d','c',30),
    ('b','c',35),
    ('c','b',35);

WITH RECURSIVE rec (start_point, end_point, path, total_cost, visited) AS (
    SELECT ro.point1, ro.point2, ARRAY[ro.point1, ro.point2], ro.cost, ARRAY[ro.point1]
    FROM routes ro
    WHERE ro.point1 = 'a'
    UNION ALL
    SELECT rec.end_point, ro.point2, rec.path || ro.point2, rec.total_cost + ro.cost, visited || rec.end_point
    FROM rec
    JOIN routes ro
    ON rec.end_point = ro.point1
    WHERE NOT (ro.point2 = ANY(visited))
),
rec_completed AS (
    SELECT rec.start_point, rec.end_point, rec.path || ro.point2 AS tour, rec.total_cost + ro.cost AS total_cost
    FROM rec
    JOIN routes ro
    ON rec.end_point = ro.point1 AND ro.point2 = 'a'
    WHERE array_length(rec.path, 1) = (SELECT COUNT(DISTINCT point1) FROM routes)
),
min_cost AS (
    SELECT MIN(total_cost) AS min_total_cost
    FROM rec_completed
)
SELECT total_cost, tour
FROM rec_completed
WHERE total_cost = (SELECT min_total_cost FROM min_cost)
ORDER BY total_cost, tour;
/*
create a table with named nodes using structure {point1, point2, cost} and fill data based on a picture 
(there are direct and reverse paths between 2 nodes). write a SQL statement that returns all tours (aka paths) 
with minimum travel cost if we start from city "a". Remember, you need to find the cheapest way to visit all 
cities and return to your starting point. For example, the tour looks like a -> b -> c -> d -> a.
sort the data by total_cost and then by tour.
*/
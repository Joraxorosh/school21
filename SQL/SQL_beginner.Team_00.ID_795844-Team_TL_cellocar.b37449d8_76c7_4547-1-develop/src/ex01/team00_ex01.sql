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
)
SELECT total_cost, tour
FROM rec_completed
ORDER BY total_cost, tour;
/*
add a way to see additional rows with the most expensive cost to the SQL from the previous exercise. 
Take a look at the sample data below. Please sort the data by total_cost and then by trip.
*/
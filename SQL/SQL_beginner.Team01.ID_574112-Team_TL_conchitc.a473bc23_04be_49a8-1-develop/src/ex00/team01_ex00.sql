WITH get_last_rate AS (
    SELECT DISTINCT ON (id) id, name, rate_to_usd AS last_rate_to_usd
    FROM currency
    ORDER BY id, updated DESC
)
SELECT
    COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    b.type,
    SUM(b.money) AS volume,
    COALESCE(glr.name, 'not defined') AS currency_name,
    COALESCE(glr.last_rate_to_usd, 1) AS last_rate_to_usd,
    SUM(b.money) * COALESCE(glr.last_rate_to_usd, 1) AS total_volume_in_usd
FROM Balance b
FULL JOIN "user" u ON b.user_id = u.id
LEFT JOIN get_last_rate glr ON b.currency_id = glr.id
GROUP BY u.id, b.type, glr.name, glr.last_rate_to_usd
ORDER BY name DESC, lastname, b.type;
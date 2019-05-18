create table agent_order
(
    id       INTEGER PRIMARY KEY AUTO_INCREMENT,
    agent_id INTEGER NOT NULL,
    order_id INTEGER NOT NULL,
    FOREIGN KEY (agent_id) REFERENCES agents (id),
    FOREIGN KEY (order_id) REFERENCES orders (id)
)
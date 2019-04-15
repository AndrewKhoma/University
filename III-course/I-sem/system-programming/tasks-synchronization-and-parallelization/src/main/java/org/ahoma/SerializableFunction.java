package org.ahoma;
/*
 * Created by ahoma on 15/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.Serializable;
import java.util.function.Function;

@FunctionalInterface
public interface SerializableFunction<I, O> extends Function<I, O>, Serializable {}

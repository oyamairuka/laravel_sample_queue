<?php

namespace App\Queue\Connectors;

use Illuminate\Queue\Connectors\ConnectorInterface;

use App\Queue\LSQQueue;

class LSQConnector implements ConnectorInterface
{
    /**
     * Establish a queue connection.
     *
     * @param array $config
     * @return \Illuminate\Contracts\Queue\Queue
     */
    public function connect(array $config)
    {
        return new LSQQueue(
            $config['host'],
            $config['port']
        );
    }
}

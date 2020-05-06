<?php

namespace App\Providers;

use Illuminate\Queue\QueueServiceProvider;

use App\Queue\Connectors\LSQConnector;

class LSQServiceProvider extends QueueServiceProvider
{
    /**
     * Register the connectors on the queue manager.
     *
     * @param \Illuminate\Queue\QueueManager $manager
     * @return void
     */
    public function registerConnectors($manager)
    {
        parent::registerConnectors($manager);
        $this->registerLSQConnector($manager);
    }

    /**
     * Register the lsq queue connector.
     *
     * @param \Illuminate\Queue\QueueManager $manager
     * @return \App\Queue\Connectors\LSQConnector
     */
    protected function registerLSQConnector($manager)
    {
        $manager->addConnector('lsq', function () {
            return new LSQConnector;
        });
    }
}

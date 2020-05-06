<?php

namespace App\Jobs;

use DateTime;

use Illuminate\Bus\Queueable;
use Illuminate\Contracts\Queue\ShouldQueue;
use Illuminate\Foundation\Bus\Dispatchable;
use Illuminate\Queue\InteractsWithQueue;
use Illuminate\Queue\SerializesModels;
use Log;

class LSQTestJob implements ShouldQueue
{
    use Dispatchable, InteractsWithQueue, Queueable, SerializesModels;

    /**
     * コントローラーがこのジョブを設定した時刻 
     *
     * @var DateTime
     */
    private $controllerDate;

    /**
     * コンストラクトされた時刻 
     *
     * @var DateTime
     */
    private $createData;

    /**
     * Create a new job instance.
     *
     * @return DateTime $dt
     */
    public function __construct(DateTime $dt)
    {
        $this->controllerDate = $dt;
        $this->createData = new DateTime();
    }

    /**
     * Execute the job.
     *
     * @return void
     */
    public function handle()
    {
        $handleDate = new DateTime();
        Log::debug(LSQTestJob::class . '::handle');
        Log::debug('controllerDate : ' . $this->controllerDate->format(DateTime::W3C));
        Log::debug('createDate : ' . $this->createData->format(DateTime::W3C));
        Log::debug('handleDate : ' . $handleDate->format(DateTime::W3C));
    }
}

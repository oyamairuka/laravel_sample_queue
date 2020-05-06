<?php

namespace App\Http\Controllers;

use DateTime;

use App\Jobs\LSQTestJob;
use Illuminate\Http\Request;
use Log;

class LSQTestController extends Controller
{
    //
    public function add()
    {
        Log::Info('LSQTestController::add');
        LSQTestJob::dispatch(new DateTime());
    }

    public function addLater()
    {
        Log::Info('LSQTestController::addLater');
        LSQTestJob::dispatch(new DateTime())->delay(now()->addMinutes(1));
    }
}

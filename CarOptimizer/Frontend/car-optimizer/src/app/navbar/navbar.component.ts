import { Component, OnInit, OnDestroy } from '@angular/core';
import { UserType } from '../services/userType.service';
import { BehaviorSubject, Subscription } from 'rxjs';

@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.css']
})
export class NavbarComponent implements OnInit, OnDestroy {

  accountType!: string;
  private subscription!: Subscription;

  constructor(private userType: UserType) { }

  ngOnInit(): void {
    this.subscription = this.userType.currentAccountType.subscribe(
      type => this.accountType = type
    );
  }

  ngOnDestroy(): void {
    this.subscription.unsubscribe();
  }
}
